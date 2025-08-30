/*
 * Problem URL : https://codeforces.com/problemset/problem/25/E
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
int lps[300005];
int calc(vector<string> &v) {
  string s = v[0];
  for (int k = 1; k < 3; k++) {
    lps[0] = 0;
    for (int i = 1, j = 0; i < v[k].size(); i++) {
      while (j && v[k][i] != v[k][j])
        j = lps[j - 1];
      if (v[k][i] == v[k][j])
        j++;
      lps[i] = j;
    }
    int j = 0;
    bool found = 0;
    for (int i = 0; i < s.size(); i++) {
      while (j == v[k].size() || (j && s[i] != v[k][j]))
        j = lps[j - 1];
      if (s[i] == v[k][j])
        j++;
      if (j == v[k].size())
        found = 1;
    }
    if (found)
      continue;
    s += v[k].substr(j);
  }
  return s.size();
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  vector<string> s(3);
  cin >> s[0] >> s[1] >> s[2];
  sort(s.begin(), s.end());
  int res = calc(s);
  while (next_permutation(s.begin(), s.end())) {
    res = min(res, calc(s));
  }
  cout << res;
  return 0;
}
