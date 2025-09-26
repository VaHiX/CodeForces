/*
 * Problem URL : https://codeforces.com/problemset/problem/626/B
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
using namespace std;
int n;
string s;
main() {
  cin >> n >> s;
  if (s == string(n, s[0]))
    cout << s[0];
  else
    for (char i : {'B', 'G', 'R'})
      if (count(s.begin(), s.end(), i) != n - 1)
        cout << i;
}