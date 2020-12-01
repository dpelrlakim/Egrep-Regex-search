// Q6 search.cc (identical to Q5)
#include <string>
#include "re.h"

using std::string;
using std::cout;
using std::endl;
using namespace CS246E;

bool containsMatch(RegExp *re, const string &s) {
  string s2 = '\200' + s + '\201';
  size_t cursor = 0, currLen = 0, sLen = s2.length();
  string temp = "";
  while (cursor < sLen) {
    temp = "";
    while (currLen <= sLen) {
      if (re->matches(temp)) return true;
      temp += s2[cursor + currLen];
      ++currLen;
    }
    currLen = 0;
    ++cursor;
  }
  return false;
}

