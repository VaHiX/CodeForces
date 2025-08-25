/*
 * Problem URL : https://codeforces.com/problemset/problem/242/E
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("03,unroll-loops")
#pragma GCC target("avx2")
const int N = 1e5 + 5;
int n, q, a[N];
int main() {
  cin.tie(0);
  cout.tie(0);
  ios_base::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  cin >> q;
  while (q--) {
    int type;
    cin >> type;
    if (type == 1) {
      int l, r;
      cin >> l >> r;
      long long ans = 0;
      for (int i = l; i <= r; i++)
        ans += a[i];
      cout << ans << '\n';
      continue;
    }
    int l, r, x;
    cin >> l >> r >> x;
    for (int i = l; i <= r; i++)
      a[i] ^= x;
  }
}
