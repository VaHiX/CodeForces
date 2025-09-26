/*
 * Problem URL : https://codeforces.com/problemset/problem/291/B
 * Submit Date : 2025-08-18
 */

#include <iostream>

using namespace std;

int main() {
  char s[100001];
  string lexeme;
  cin.getline(s, sizeof(s) / sizeof(s[0]));
  char *p = s;
  bool quote(false);
  while (*p != 0) {
    if (quote) {
      if (*p != '\"') {
        lexeme.push_back(*p);
      } else {
        cout << "<" << lexeme << ">" << endl;
        lexeme.clear();
        quote = false;
      }
    } else {
      if (*p == '\"') {
        quote = true;
      } else if (*p == ' ') {
        if (!lexeme.empty()) {
          cout << "<" << lexeme << ">" << endl;
          lexeme.clear();
        }
      } else {
        lexeme.push_back(*p);
      }
    }
    ++p;
  }
  if (!lexeme.empty()) {
    cout << "<" << lexeme << ">" << endl;
  }
  return 0;
}
