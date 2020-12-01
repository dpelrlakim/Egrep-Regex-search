// Q6 re.h (identical to Q5)
#include <iostream>
#include <string>
#include <memory>

using std::string;
using std::unique_ptr;
using std::ostream;

namespace CS246E {

class RegExp {
 public:
 	virtual void identify() const = 0; // debugging helper
	virtual ostream &print(ostream &out) const = 0;
	virtual bool canBeEmpty() const = 0;
 	virtual ~RegExp();
 	virtual bool matches(const string &s) const = 0;
};

class Begin: public RegExp {
 public:
 	void identify() const override;
 	ostream &print(ostream &out) const override;
 	bool canBeEmpty() const override;
 	bool matches(const string &s) const override;
};

class End: public RegExp {
 public:
 	void identify() const override;
 	ostream &print(ostream &out) const override;
 	bool canBeEmpty() const override;
 	bool matches(const string &s) const override;
};

class Disjunction: public RegExp {
	unique_ptr<RegExp> re1;
	unique_ptr<RegExp> re2;
 public:
 	void identify() const override;
	ostream &print(ostream &out) const override;
 	Disjunction(unique_ptr<RegExp> &&expr1, unique_ptr<RegExp> &&expr2);
 	bool canBeEmpty() const override;
 	bool matches(const string &s) const override;
};

class Concatenation: public RegExp {
	unique_ptr<RegExp> re1;
	unique_ptr<RegExp> re2;
 public:
	void identify() const override;
	ostream &print(ostream &out) const override;
 	Concatenation(unique_ptr<RegExp> &&expr1, unique_ptr<RegExp> &&expr2);
 	bool canBeEmpty() const override;
 	bool matches(const string &s) const override;
};

class Star: public RegExp {
	unique_ptr<RegExp> re;
 public:
	void identify() const override;
	ostream &print(ostream &out) const override;
 	Star(unique_ptr<RegExp> &&re);
 	bool canBeEmpty() const override;
 	bool matches(const string &s) const override;
};

class Dot: public RegExp {
 public:
	void identify() const override;
	ostream &print(ostream &out) const override;
 	bool canBeEmpty() const override;
 	bool matches(const string &s) const override;
};

class Word: public RegExp {
	string wrd;
 public:
	void identify() const override;
	ostream &print(ostream &out) const override;
 	Word(string s);
 	bool canBeEmpty() const override;
 	bool matches(const string &s) const override;
};

unique_ptr<RegExp> parseWord(const string &s);
unique_ptr<RegExp> parseStar(const string &s);
unique_ptr<RegExp> parseConcatenation(const string &s);
unique_ptr<RegExp> parseDisjunction(const string &s);
ostream &operator<<(ostream &out, RegExp &re);

}

bool containsMatch(CS246E::RegExp *re, const string &s);



