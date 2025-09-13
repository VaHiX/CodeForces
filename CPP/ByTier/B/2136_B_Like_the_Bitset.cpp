/*
 * Problem URL : https://codeforces.com/contest/2136/problem/B
 * Submit Date : 2025-08-30
 */

#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, k;
  string s;
  cin >> n >> k >> s;
  int mx = 0, cur = 0;
  for (char c : s) {
    if (c == '1')
      cur++;
    else {
      if (cur > mx)
        mx = cur;
      cur = 0;
    }
  }
  if (cur > mx)
    mx = cur;
  if (mx >= k)
    cout << "NO\n";
  else {
    int cnt = count(s.begin(), s.end(), '1');
    int sm = 1, lg = cnt + 1;
    cout << "YES\n";
    for (char c : s) {
      if (c == '1')
        cout << sm++ << " ";
      else
        cout << lg++ << " ";
    }
    cout << "\n";
  }
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}