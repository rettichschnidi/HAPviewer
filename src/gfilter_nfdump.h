#ifndef GFILTER_NFDUMP_H_
#define GFILTER_NFDUMP_H_

/**
 *	\file gfilter_nfdump.h
 *	\brief Filter to import nfdump files
 *
 * 	This file is subject to the terms and conditions defined in
 * 	files 'BSD.txt' and 'GPL.txt'. For a list of authors see file 'AUTHORS'.
 */

#include <string>

#include "gfilter.h"

/**
 *	\class	GFilter_nfdump
 *	\brief	GFilter_nfdump is an class which can import nfdump files
 */
class GFilter_nfdump: public GFilter {
	public:
		GFilter_nfdump(std::string name = "nfdump", std::string simplePattern = "nfcapd*", std::string regexPattern = "^nfcapd.*");
		virtual void read_file(std::string in_filename, CFlowList & flowlist, const IPv6_addr & local_net, const IPv6_addr & netmask, bool append) const;
		virtual bool acceptFileForReading(std::string in_filename) const;
};

#endif /* GFILTER_NFDUMP_H_ */
