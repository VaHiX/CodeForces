/*
 * Problem URL : https://codeforces.com/problemset/problem/2053/F
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
#define ll long long
#define vector basic_string
#define pb push_back
#define SZ(x) (int)(x).size()
using namespace std;
const int N = 2e5 + 5, M = 6e5 + 5;
int _, n, m, k, x, c[M];
ll ans;
vector<int> a[N];
struct DS {
  ll f[M], ad, mx, an;
  inline void clr() {
    ad = mx = an = 0;
    for (int i = 1; i <= k; i++)
      f[i] = 0;
  }
  inline void Add(ll v) { ad += v, mx += v, an += v; }
  inline void Max(ll v) { mx = max(mx, v), an = max(an, v); }
  inline void add(int x, ll v) {
    an = max(an, f[x] = max(f[x] + ad, mx) + v), f[x] -= ad;
  }
} S;
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> _;
  while (_--) {
    cin >> n >> m >> k;
    ans = 0;
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++)
        if (cin >> x, ~x)
          a[i].pb(x);
    for (int i = 1; i < n; i++) {
      for (int j : a[i])
        c[j]++;
      for (int j : a[i + 1])
        ans += c[j];
      for (int j : a[i])
        c[j] = 0;
    }
    S.clr();
    for (int i : a[2])
      S.add(i, m - SZ(a[1]));
    for (int i = 2; i <= n; i++) {
      int x = S.an, e = m - SZ(a[i]);
      S.Add(1ll * e * (m - SZ(a[i - 1])));
      S.Max(x);
      for (int j : a[i - 1])
        S.add(j, e);
      if (i < n)
        for (int j : a[i + 1])
          S.add(j, e);
    }
    cout << S.an + ans << '\n';
    for (int i = 1; i <= n; i++)
      a[i].clear();
  }
  return 0;
}