/*
 * Problem URL : https://codeforces.com/contest/1404/problem/A
 * Submit Date : 2025-09-01
 */

// LUOGU_RID: 151693856
#include <bits/stdc++.h>
using namespace std;
bool solve() {
  int n, k, c0 = 0, c1 = 0;
  string s;
  cin >> n >> k >> s;
  string t(k, '?');
  for (int i = 0; i < n; i++)
    if (s[i] != '?') {
      if (t[i % k] == '?')
        t[i % k] = s[i];
      else if (t[i % k] != s[i])
        return 0;
      t[i % k] = s[i];
    }
  for (int i = 0; i < k; i++) {
    if (t[i] == '1')
      c1++;
    if (t[i] == '0')
      c0++;
  }
  return c0 <= k / 2 && c1 <= k / 2;
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int t;
  cin >> t;
  while (t--)
    cout << (solve() ? "YES\n" : "NO\n");
  return 0;
}