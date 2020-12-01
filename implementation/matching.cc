// Q6 matching.cc (identical to Q5)
#include <string>
#include <iostream>
#include <utility>
#include <memory>
#include "re.h"

using std::string;
using std::unique_ptr;
namespace CS246E {

RegExp::~RegExp() {}

bool Begin::canBeEmpty() const { return false; }
bool Begin::matches(const string &s) const { return s.compare("\200") == 0; }

bool End::canBeEmpty() const { return false; }
bool End::matches(const string &s) const { return s.compare("\201") == 0; }

bool Dot::canBeEmpty() const { return false; }
bool Dot::matches(const string &s) const { return s.length() == 1; }

Disjunction::Disjunction(unique_ptr<RegExp> &&expr1, unique_ptr<RegExp> &&expr2): 
	re1{std::move(expr1)}, re2{std::move(expr2)} {};
bool Disjunction::canBeEmpty() const { return re1->canBeEmpty() || re2->canBeEmpty(); }
bool Disjunction::matches(const string &s) const { return re1->matches(s) || re2->matches(s); }

Concatenation::Concatenation(unique_ptr<RegExp> &&expr1, unique_ptr<RegExp> &&expr2): 
	re1{std::move(expr1)}, re2{std::move(expr2)} {};
bool Concatenation::canBeEmpty() const { return re1->canBeEmpty() && re2->canBeEmpty(); }
bool Concatenation::matches(const string &s) const {
	if (s.empty()) return canBeEmpty();
	size_t split = 0, maximal = 0, sLen = s.length();
	while (split <= sLen) {
		if (re1->matches(s.substr(0, split))) {
			maximal = split;
			if (re2->matches(s.substr(split, sLen - split))) return true;
		}
		++split;
	}
	return false;
}

Star::Star(unique_ptr<RegExp> &&expr): re{std::move(expr)} {}
bool Star::canBeEmpty() const { return true; }
bool Star::matches(const string &s) const {
	if (s.empty()) return true;
	const size_t sLen = s.length();
	size_t counter = 1, unchecked = 0;
	while (unchecked + counter <= sLen) {
		if (re->matches(s.substr(unchecked, counter))) {
			unchecked += counter;
			counter = 0;
		}
		++counter;
	}
	return unchecked == sLen;
}

Word::Word(string s): wrd{std::move(s)} {};
bool Word::canBeEmpty() const { return wrd.empty(); }
bool Word::matches(const string &s) const { return !wrd.compare(s); }

}

