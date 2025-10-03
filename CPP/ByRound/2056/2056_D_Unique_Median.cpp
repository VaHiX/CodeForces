/*
 * Problem URL : https://codeforces.com/problemset/problem/2056/D
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 1e5 + 5;
int T, n, a[maxn], s, t;
int c[maxn * 2];
ll ans;
map<int, int> mp;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> T;
  while (T--) {
    cin >> n;
    ans = 1ll * n * (n + 1) / 2;
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    for (int k = 1; k <= 10; k++) {
      mp[0] = 1;
      s = t = n;
      for (int i = 1, j = 1; i <= n; i++) {
        if (a[i] == k)
          while (j <= i) {
            c[t]++;
            t += a[j++] > k ? 1 : -1;
          }
        s += a[i] > k ? 1 : -1;
        ans -= c[s];
      }
      for (int i = 0; i <= 2 * n; i++)
        c[i] = 0;
    }
    cout << ans << '\n';
  }
  return 0;
}