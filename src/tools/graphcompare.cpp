/**
 *	\file graphcompare.cpp
 *
 * 	This file is subject to the terms and conditions defined in
 * 	files 'BSD.txt' and 'GPL.txt'. For a list of authors see file 'AUTHORS'.
 */

#include <iostream>
#include <string>
#include <cstdlib>

#include "graph.h"

using namespace std;

int main(int argc, char **argv) {
	if (argc != 3) {
		cerr << "Usage: ./graphcompare /path/to/graphA.dot /path/to/graphB.dot [or - to read from stdin instead of graphB.dot]" << endl;
		exit(1);
	}

	try {
		ifstream inputA(argv[1]);
		istream *inputB;

		if(string(argv[2]) == "-") {
			inputB = &cin;
		} else {
			inputB = new ifstream(argv[2]);
		}

		DotGraph graphA(inputA);
		DotGraph graphB(*inputB);

		bool equality = graphA.diffGraphVerbose(graphB);
		if (equality) {
			return 0;
		} else {
			if(graphA.isomorphism(graphB)) {
				cout << "Graphs are isomorph." << endl;
			} else {
				cout << "Graphs are not isomorph." << endl;
			}
			return 1;
		}
	} catch (std::string &e) {
		cerr << "Error: " << e << endl;
		return 2;
	} catch (...) {
		cerr << "Unknown error..." << endl;
		return 3;
	}
}
