/*
 * Problem URL : https://codeforces.com/contest/2029/problem/C
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
using namespace std;

inline void solve() {
  int n;
  cin >> n;

  int x = 0, y = 0, z = -1;
  for (int i = 1; i <= n; ++i) {
    int a;
    cin >> a;

    if (x < a)
      ++x;
    if (x > a)
      --x;

    if (z < a)
      ++z;
    if (z > a)
      --z;

    z = max(z, y), y = max(y, x);
  }

  cout << z << "\n";
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);

  int t;
  cin >> t;
  while (t--)
    solve();

  return 0;
}
