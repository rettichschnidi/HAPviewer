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
		cerr << "Usage: ./graphcompare /path/to/graphA.dot /path/to/graphB.dot" << endl;
		exit(1);
	}

	try {
		ifstream inputA(argv[1]);
		ifstream inputB(argv[2]);

		DotGraph graphA(inputA);
		DotGraph graphB(inputB);

		bool equality = graphA.equalVerbose(graphB);
		if (equality) {
			cout << "Graphs are equal." << endl;
			return 0;
		} else {
			return 1;
		}
	} catch (std::string &e) {
		cerr << "Error: " << e << endl;
		return 111;
	} catch (...) {
		cerr << "Unknown error..." << endl;
		return 112;
	}
}
