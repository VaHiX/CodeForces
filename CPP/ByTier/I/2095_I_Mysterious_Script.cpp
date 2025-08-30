/*
 * Problem URL : https://codeforces.com/problemset/problem/2095/I
 * Submit Date : 2025-08-20
 */

#include <bits/stdc++.h>
using namespace std;

string s, t, oo,
    ss[] = {"la", "le", "lon", "sha", "she", "shon", "ta", "te", "ton"};
long long o;

long long trans(string s) {
  long long o = 0;
  for (int i = 0; i < s.length() - 1;) {
    o *= 9;
    for (int j = 0; j <= 9; ++j)
      if (s.find(ss[j], i) == i) {
        o += j;
        i += ss[j].length();
        break;
      }
  }
  return o;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin >> s >> t;
  o = trans(s) + trans(t);
  oo = "s";
  while (o) {
    oo = ss[o % 9] + oo;
    o /= 9;
  }
  cout << oo << "\n";
  return 0;
}