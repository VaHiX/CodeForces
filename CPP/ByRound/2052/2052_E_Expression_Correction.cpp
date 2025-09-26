/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>

#define int int64_t
using namespace std;

bool check(string s) {
  array<int, 2> n = {0, 0};
  int ni = 0;
  bool neg = 0;
  int cn = 0;
  s.push_back('=');
  bool last_is_digit = 0;
  bool lz = 0;
  for (auto &c : s) {
    if (c == '-' || c == '+' || c == '=') {
      if (!last_is_digit)
        return 0;
      last_is_digit = 0;
      if (neg)
        n[ni] -= cn;
      else
        n[ni] += cn;
      neg = 0;
      cn = 0;
      lz = 0;
    }
    if (c >= '0' && c <= '9') {
      if (lz)
        return 0;
      int d = c - '0';
      cn = cn * 10 + d;
      if (d == 0 && !last_is_digit)
        lz = 1;
      last_is_digit = 1;
    }
    if (cn > 9999999999)
      return 0;
    if (c == '-')
      neg = !neg;
    if (c == '=')
      ni++;
  }
  return n[0] == n[1];
}

signed main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  string s;
  cin >> s;
  if (check(s)) {
    cout << "Correct\n";
    return 0;
  }
  for (int i = 0; i < s.size(); ++i) {
    if (s[i] >= '0' && s[i] <= '9') {
      string s2 = s;
      s2.erase(s2.begin() + i);
      for (int j = 0; j <= s2.size(); ++j) {
        string s3 = s2;
        // cerr<<"trying "<<s3<<endl;
        s3.insert(s3.begin() + j, s[i]);
        if (check(s3)) {
          cout << s3 << '\n';
          return 0;
        }
      }
    }
  }
  cout << "Impossible\n";
  return 0;
}
