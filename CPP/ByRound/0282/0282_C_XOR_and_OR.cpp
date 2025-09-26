/*
 * Problem URL : https://codeforces.com/problemset/problem/282/C
 * Submit Date : 2025-08-09
 */

#include <iostream>

using namespace std;

int main() {
  string a, b;
  cin >> a >> b;
  bool can(false);
  if (a.length() == b.length()) {
    size_t ia(0), ib(0);
    while (ia < a.length() && a[ia] == '0')
      ++ia;
    while (ib < b.length() && b[ib] == '0')
      ++ib;
    if ((ia < a.length() && ib < b.length()) ||
        (ia == a.length() && ib == b.length()))
      can = true;
  }
  cout << (can ? "YES" : "NO") << endl;
  return 0;
}
