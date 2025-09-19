/*
 * Problem URL : https://codeforces.com/contest/2028/problem/F
 * Submit Date : 2025-09-09
 */

// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#pragma GCC optimize("Ofast", "unroll-loops", "inline")
#include <bits/stdc++.h>
#define ll long long
// #define int ll
#define pb push_back
#define pii pair<int, int>
#define MP make_pair
#define fi first
#define se second
using namespace std;
const int N = 2e5 + 60, M = 1e4 + 2, mod = 998244353;
bitset<M> b[16], f, g, z;
int p[16], o;
int a[N], n, m;
inline int lst(int x) { return (x + 15) & 15; }
void solve() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  for (int i = 0; i < 16; i++)
    b[i].reset(), p[i] = -1;
  g.reset(), z.reset();
  f.reset();
  g.set(0), o = 0, b[o].set(0), p[o] = a[1];
  if (!a[1])
    z.set(0);
  for (int i = 1; i <= n; i++) {
    f.reset();
    for (int u = o, k = p[o]; lst(u) != o && k > 0 && k <= m;
         u = lst(u), k = k * p[u])
      f |= b[u] << k;
    f |= z;
    if (i != n) {
      if (p[o] == 1)
        p[o] = a[i + 1], b[o] |= f;
      else
        o = (o + 1) & 15, p[o] = a[i + 1], b[o] = f;
      g |= f;
      if (!a[i + 1])
        z = g;
    }
  }
  cout << (f[m] ? "YES" : "NO") << '\n';
}
signed main() {
  //	freopen("f.in","r",stdin);
  //	freopen("f.out","w",stdout);
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int T;
  cin >> T;
  while (T--)
    solve();
  return 0;
}