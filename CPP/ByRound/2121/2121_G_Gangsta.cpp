/*
 * Problem URL : https://codeforces.com/problemset/problem/2121/G
 * Submit Date : 2025-08-14
 */

#include <bits/stdc++.h>
#define int long long
#define N 200005
using namespace std;

int t, n, ans;
string s;

int f[N];

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> t;
  while (t--) {
    cin >> n >> s;
    for (int i = 1; i <= n; ++i)
      f[i] = f[i - 1] + (s[i - 1] == '1' ? 1 : -1);
    sort(f, f + n + 1);
    ans = 0;
    for (int i = 0; i <= n; ++i)
      ans += f[i] * (2 * i - n);
    ans += n * (n + 1) * (n + 2) / 6;
    cout << (ans >> 1) << '\n';
  }
  return 0;
}
