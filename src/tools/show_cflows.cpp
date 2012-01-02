/**
 *	\file	show_cflows.cpp
 *
 *	Show contents of a "cflow_t" file as human readable text.
 *
 *
 * 	Copyright (c) 2009, Eduard Glatz 
 *
 * 	Author: Eduard Glatz  (eglatz@tik.ee.ethz.ch) 
 *
 *
 */

#include "cflow.h"
#include "gfilter_cflow.h"
#include "gutil.h"
#include "gimport.h"

#include <iostream>
#include <fstream>
#include <string>
#include <limits>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/program_options.hpp>

using namespace std;

/**
 * Purge all flows which do not fit the given pattern.
 *
 * \param pattern cflow struct which has all relevant fields set to MAXVAL
 * and the rest to 0
 * \param value cflow with the values to compare with
 * \param list cflowlist
 * \return
 */
bool purge(cflow_t &pattern, const cflow_t &value, CFlowList &list) {
	CFlowList rest;
	cflow_t currentItem;

	for(unsigned int i = 0; i < list.size(); i++) {
		currentItem = list[i];
		currentItem &= pattern;
		if(currentItem == value) {
			rest.push_back(list[i]);
		}
	}
	list = rest;
}

int main(int argc, char * argv[]) {
	// 1. Process command line
	// ***********************
	//
	// Check for needed command line arguments and process supported command line options
	boost::program_options::variables_map variablesMap;
	boost::program_options::options_description desc("Allowed options");

	bool append = false;
	cflow_t pattern;
	cflow_t value;

	try {
		desc.add_options()
				("inputfile,i", boost::program_options::value<string>(), "File to read")
				("textdump,o", boost::program_options::value<string>(), "Produce a text output file")
				("cflowdump,w", boost::program_options::value<string>(), "Produce a cflow output file")
				("limit,l", boost::program_options::value<int>(), "Count of flows to display (default: all)")
				("localPort", boost::program_options::value<uint16_t>(&value.localPort)->default_value(0), "show only flows with this localPort")
				("remotePort", boost::program_options::value<uint16_t>(&value.remotePort)->default_value(0), "show only flows with this remotePort")
				("countonly,c", "Do count only (no other output)")
				("verbose,v", "Verbose output")
				("append,a", "Try to append to a possibly already existing file")
				("help,h", "show this help message")
			;

		boost::program_options::positional_options_description posOpt;
		posOpt.add("inputfile", -1);

		boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), variablesMap);
		boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(desc).positional(posOpt).run(), variablesMap);
		boost::program_options::notify(variablesMap);
	} catch (std::exception & e) {
		std::cerr << "Error: " << e.what() << std::endl;
		exit(1);
	}

	if (variablesMap.count("help")) {
		cerr << desc;
		exit(0);
	}

	if (!variablesMap.count("inputfile")) {
		cerr << desc;
		exit(1);
	}

	GFilter_cflow4 *filter_cflow4 = new GFilter_cflow4;
	GFilter_cflow6 *filter_cflow6 = new GFilter_cflow6;
	GFilter_cflow *filter_cflow;
	int oldmagic = -1;
	string infile = variablesMap["inputfile"].as<string>();

	string cflowdump;
	if(variablesMap.count("cflowdump"))
		cflowdump = variablesMap["cflowdump"].as<string>();
	append = variablesMap.count("append");

	// 2. Check and open input file
	// ****************************
	try {
		if (filter_cflow6->acceptFileForReading(infile)) {
			filter_cflow = filter_cflow6;
			oldmagic = CFLOW_6_MAGIC_NUMBER;
		} else if (filter_cflow4->acceptFileForReading(infile)) {
			filter_cflow = filter_cflow4;
			oldmagic = CFLOW_4_MAGIC_NUMBER;
		} else {
			string e = "Can not handle this file";
			throw e;
		}
	} catch (string & e) {
		cerr << e << endl;
		exit(1);
	}

	//	3. Process input file data
	//	**************************
	//	Read records from file
	//	- show input data interpreted as "cflow_t" records on console in text form
	//	- write console text to optional output file (option -o)
	//	- write binary records to optional output file (option -w)

	CFlowList cflowlist;
	/**
	 * Read given input file into memory.
	 */
	try {
		filter_cflow->read_file(infile, cflowlist);
	} catch (string & e) {
		cerr << e << endl;
		exit(1);
	}

	bool filteringNeeded = false;
	if(value.localPort != 0) {
		pattern.localPort = numeric_limits<uint16_t>::max();
		filteringNeeded = true;
	}

	if(value.remotePort != 0) {
		pattern.remotePort = numeric_limits<uint16_t>::max();
		filteringNeeded = true;
	}

	if(filteringNeeded) {
		purge(pattern, value, cflowlist);
	}

	/**
	 * If user just wants to know the number of flows, print this value and exit.
	 */
	if (variablesMap.count("countonly")) {
		cout << "Number of cflows: " << cflowlist.size() << endl;
		exit(0);
	}

	/**
	 * If user set a limit, compare to the number of flows and use the smaller
	 * number as limit.
	 */
	unsigned int limit = cflowlist.size();
	if (variablesMap.count("limit") && ((int) limit > variablesMap["limit"].as<int>()))
		limit = variablesMap["limit"].as<int>();

	/**
	 * If user wants to have the output dumped into a file, then do this now.
	 */
	if (variablesMap.count("textdump")) {
		string textoutputname = variablesMap["textdump"].as<string>();
		ofstream text_ofstream(textoutputname.c_str());

		for (unsigned int i = 0; (i < limit) && text_ofstream.good(); i++) {
			text_ofstream << cflowlist[i] << ", oldmagic: " << oldmagic << endl;
		}
	}

	/**
	 * Print flows to stdout.
	 */
	for (unsigned int i = 0; i < limit; i++) {
		cout << cflowlist[i] << ", oldmagic: " << oldmagic << endl;
	}

	/**
	 * If user wants to have new cflow file written, do this now.
	 */
	if(variablesMap.count("cflowdump")) {
		try {
			filter_cflow6->write_file(cflowdump, cflowlist, append);
		}
		catch(string & e) {
			cerr << e << endl;
			exit(1);
		}
	}
	return 0;
}

