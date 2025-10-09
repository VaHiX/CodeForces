/*
 * Problem URL : https://codeforces.com/problemset/problem/1265/A
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>
using namespace std;
int i, p, t;
string s;
main() {
  for (cin >> t; t--;) {
    for (cin >> s, i = p = 0; s[i]; i++)
      if (s[i] > 96 & s[i] == s[i + 1])
        p = 1;
      else if (s[i] < 96)
        s[i] = i ? s[i - 1] % 3 + 97 : 97,
        s[i] == s[i + 1] ? s[i] = s[i] % 3 + 97 : 0;
    cout << (p ? "-1" : s) << endl;
  }
}