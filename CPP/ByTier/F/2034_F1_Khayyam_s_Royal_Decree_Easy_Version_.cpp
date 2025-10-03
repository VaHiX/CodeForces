/*
 * Problem URL : https://codeforces.com/contest/2034/problem/F1
 * Submit Date : 2025-09-07
 */

#include <bits/stdc++.h>
#define int long long

using namespace std;
using Pii = pair<int, int>;

const int N = 5e3 + 5, L = 4e5 + 5, P = 998244353;

int t, n, m, k, f[L], I[L], g[N], r;
Pii a[N];

int Q(int x, int y) {
  if (!y) {
    return 1;
  }
  int z = Q(x, y / 2);
  return z * z % P * (y & 1 ? x : 1) % P;
}

int C(int x, int y) { return f[x] * I[y] % P * I[x - y] % P; }

signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  f[0] = I[0] = 1;
  for (int i = 1; i < L; i++) {
    f[i] = f[i - 1] * i % P;
  }
  I[L - 1] = Q(f[L - 1], P - 2);
  for (int i = L - 2; i; i--) {
    I[i] = I[i + 1] * (i + 1) % P;
  }
  for (cin >> t; t--; fill(g, g + k + 1, r = 0)) {
    cin >> n >> m >> k;
    for (int i = 1; i <= k; i++) {
      cin >> a[i].first >> a[i].second;
      a[i].first = n - a[i].first;
      a[i].second = m - a[i].second;
    }
    sort(a + 1, a + k + 1);
    for (int i = 1; i <= k; i++) {
      g[i] = C(a[i].first + a[i].second, a[i].first) *
             (2 * a[i].first + a[i].second) % P;
      for (int j = 0; j < i; j++) {
        if (a[j].second <= a[i].second) {
          g[i] = (g[i] +
                  g[j] * C(a[i].first + a[i].second - a[j].first - a[j].second,
                           a[i].first - a[j].first)) %
                 P;
        }
      }
      r = (r + g[i] * C(n - a[i].first + m - a[i].second, n - a[i].first)) % P;
    }
    cout << (r + (2 * n + m) * C(n + m, n)) % P * Q(C(n + m, n), P - 2) % P
         << '\n';
  }
  return 0;
}