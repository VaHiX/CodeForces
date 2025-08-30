/*
 * Problem URL : https://codeforces.com/problemset/problem/259/A
 * Submit Date : 2025-08-09
 */

#include <iostream>
#include <string>

using namespace std;

int main() {
  bool fail(false);
  string s;
  for (int i = 0; i < 8; ++i) {
    cin >> s;
    for (size_t j = 1; j < s.length(); ++j) {
      if (s[j] == s[j - 1]) {
        fail = true;
      }
    }
  }
  cout << (fail ? "NO" : "YES") << endl;
  return 0;
}
