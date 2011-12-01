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

	ifstream inputA(argv[1]);
	ifstream inputB(argv[2]);

	try {
		DotGraph graphA(inputA);
		DotGraph graphB(inputB);

		cout << "Test for equality: ";
		bool equality = graphA.equal(graphB);
		cout << "Graphs are" << (equality ? "" : " not") << " equal" << endl;
	} catch (std::string &e) {
		cerr << e << endl;
	}
	return 1;
}
