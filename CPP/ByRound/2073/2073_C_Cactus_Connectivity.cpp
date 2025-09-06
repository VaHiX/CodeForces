/*
 * Problem URL : https://codeforces.com/contest/2073/problem/C
 * Submit Date : 2025-08-25
 */

#include <bits/stdc++.h>
#define N 500005
#define M 505
#define LL long long
#define inf 2147483647
#define LD long double
#define eps 1e-6
using namespace std;
int n, m, f[N], c[N], u[N], v[N], ans;
bool vis[N];
int tot, fir[N], nxt[N << 1], son[N << 1];

inline void add(int x, int y) {
  son[++tot] = y, nxt[tot] = fir[x], fir[x] = tot;
}

inline int gf(int x) { return f[x] == x ? x : f[x] = gf(f[x]); }
inline void dfs(int x, int fa) {
  c[x] = c[fa] ^ 1, vis[x] = 1;
  for (int i = fir[x]; i; i = nxt[i])
    if (son[i] ^ fa)
      dfs(son[i], x);
}
inline void solve(int tc) {
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    f[i] = i;
  for (int i = 1, x, y; i <= m; i++)
    cin >> x >> y, (gf(x) ^ gf(y)) && (f[f[x]] = f[y], add(x, y), add(y, x), 0),
        u[i] = x, v[i] = y;
  for (int i = 1; i <= n; i++)
    if (!vis[i])
      dfs(i, 0);
  for (int i = 1; i <= m; i++)
    if (c[u[i]] ^ c[v[i]])
      ans++;
  cout << ans + 1 << '\n';
}
int main() {

  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int tc = 1;

  while (tc--)
    solve(tc);
  return 0;
}