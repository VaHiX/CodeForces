/*
 * Problem URL : https://codeforces.com/contest/860/problem/A
 * Submit Date : 2025-09-04
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  string s;
  cin >> s;
  auto isa = [](char c) {
    vector<char> g = {'a', 'e', 'u', 'i', 'o', ' '};
    for (char t : g) {
      if (c == t)
        return false;
    }
    return true;
  };
  string ans = "";
  ans += s[0];
  if (s.size() > 1)
    ans += s[1];
  int n = s.size();
  for (int i = 2; i < n; ++i) {
    int w = ans.size();
    if (isa(ans[w - 2]) and isa(ans[w - 1]) and isa(s[i]))
      if (ans[w - 1] != ans[w - 2] or s[i] != ans[w - 1])
        ans += ' ';
    ans += s[i];
  }
  cout << ans << '\n';
}