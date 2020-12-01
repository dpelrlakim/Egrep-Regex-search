// Q6 parsing.cc (identical to Q5)
#define DEBUGGING 0
#include <iostream>
#include <string>
#include <memory>
#include "re.h"

using std::string;
using std::unique_ptr;
using std::make_unique;
using std::ostream;
using std::cout;

namespace CS246E {

void Begin::identify() const { cout << "Begin\n"; }
void End::identify() const { cout << "End\n"; }
void Disjunction::identify() const { cout << "disjunction\n"; }
void Concatenation::identify() const { cout << "Concatenation\n"; }
void Star::identify() const { cout << "Star\n"; }
void Dot::identify() const {cout << "Dot\n"; }
void Word::identify() const { cout << "Word\n"; }

ostream &Begin::print(ostream &out) const { return out << "^"; }
ostream &End::print(ostream &out) const { return out << "$"; }
ostream &Dot::print(ostream &out) const { return out << "."; }

ostream &Disjunction::print(ostream &out) const {
	out << "Disjunction (";
	re1->print(out);
	out << ",";
	re2->print(out);
	out << ")";
	return out;
}

ostream &Concatenation::print(ostream &out) const {
	out << "Concatenation (";
	re1->print(out);
	out << ",";
	re2->print(out);
	out << ")";
	return out;
}

ostream &Star::print(ostream &out) const {
	out << "Star (";
	re->print(out);
	out << ")";
	return out;
}

ostream &Word::print(ostream &out) const {
	if (wrd.length() <= 1) return out << wrd; 

	size_t i = 0;
	while (i < wrd.length() - 1) {
		out << "Concatenation (";
		out << wrd[i];
		out << ",";
		++i;
	}
	out << wrd[i];
	while (i > 0) {
		--i;
		out << ")";
	}
	return out;
}

ostream &operator<<(ostream &out, RegExp &re) {
#if DEBUGGING
	re.identify();
#endif
	return re.print(out);
}

unique_ptr<RegExp> parseWord(const string &s) {
	if (s.compare("^") == 0) return make_unique<Begin>();
	if (s.compare("$") == 0) return make_unique<End>();
	if (s.compare(".") == 0) return make_unique<Dot>();
	return make_unique<Word> (s);
}

unique_ptr<RegExp> parseStar(const string &s) {
	if (s.empty() || s.back() != '*') return parseWord(s);
	return make_unique<Star> (parseDisjunction(s.substr(0, s.length() - 1)));
}

unique_ptr<RegExp> parseConcatenation(const string &s) {
	if (s.empty()) return parseStar(s);
	size_t sLen = s.length(), split = 0;

	int openParens = 0;
	while (split < sLen) {
		if (s[split] == '(') ++openParens;
		else if (s[split] == ')') --openParens;
		++split;
		if (!openParens && split < sLen && s[split] != '*') break;
	}

	const string first = s.substr(0, split);
	const string second = s.substr(split, sLen - split);
	
	if (second.empty()) { // not a concatenation
		if (s.front() == '(' && s.back() == ')') return parseDisjunction(s.substr(1, sLen - 2));
		return parseStar(s);
	}

	return make_unique<Concatenation> (parseDisjunction(first), parseDisjunction(second));
}

unique_ptr<RegExp> parseDisjunction(const string &s) {
	size_t sLen = s.length(), split = 0;

	int openParens = 0;
	while (split < sLen) {
		if (s[split] == ')') ++openParens;
		else if (s[split] == '(') --openParens;
		else if (!openParens && s[split] == '|') break;
		++split;
	}
	
	if (split == sLen) return parseConcatenation(s);
	const string first = s.substr(0, split);
	const string second = s.substr(split + 1, sLen - (split + 1));

	return make_unique<Disjunction> (parseDisjunction(first), parseDisjunction(second));
}

}
