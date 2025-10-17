/*
 * Problem URL : https://codeforces.com/contest/1503/problem/A
 * Submit Date : 2025-09-01
 */

#include <bits/stdc++.h>
using namespace std;

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t, n;
  string s, a, b;
  cin >> t;
  while (t--) {
    cin >> n >> s;
    int cnt = 0, k = 0;
    for (char i : s)
      cnt += i == '1';
    if (cnt & 1 || s[0] == '0' || s.back() == '0') {
      cout << "NO\n";
      continue;
    }
    a = b = "";
    bool flip = false;
    for (char i : s) {
      if (i == '1') {
        a += k << 1 < cnt ? '(' : ')';
        b += a.back();
        k++;
      } else {
        a += flip ? '(' : ')';
        b += flip ? ')' : '(';
        flip = !flip;
      }
    }
    cout << "YES\n" << a << '\n' << b << '\n';
  }
  return 0;
}