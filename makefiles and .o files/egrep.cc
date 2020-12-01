#include <iostream>
#include <fstream>
#include <string>
#include "re.h"

using namespace std;

bool searchStream(istream &in, CS246E::RegExp *re, const string &name) {
	string s;
	bool found = false;
	while (getline(in, s)) {
		if (containsMatch(re, s)) {
			found = true;
			if (!name.empty()) cout << name << ":";
			cout << s << endl;
		}
	}
	return found;
}

int main(int argc, char *argv[]) {
	if (argc <= 1) {
		cerr << "argument not specified\n";
		return 1;
	}

	string pattern = argv[1];
	auto re = CS246E::parseDisjunction(pattern);

	string s;
	bool found = false;
	if (argc == 2) found = searchStream(cin, re.get(), "");
	else {
		for (size_t i = 2; i < argc; ++i) {
			string name = argv[i];
			ifstream f {name};
			f >> std::noskipws;
			bool temp = false;
			if (argc == 3) temp = searchStream(f, re.get(), "");
			else temp = searchStream(f, re.get(), name);
			if (temp) found = true;
		}
	}
	if (!found) {
		cerr << "match not found\n";
		return 1;
	}
}
