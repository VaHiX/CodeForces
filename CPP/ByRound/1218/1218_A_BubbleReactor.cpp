/*
 * Problem URL : https://codeforces.com/contest/1218/problem/A
 * Submit Date : 2025-09-02
 */

// LUOGU_RID: 162676302
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1.5e4 + 10;
int n, m;
vector<int> e[N];
namespace Tree {
int sz[N], f[N], g[N];
void Dfs(int u, int fa) {
  sz[u] = 1;
  for (int v : e[u]) {
    if (v == fa)
      continue;
    Dfs(v, u);
    f[u] += f[v];
    sz[u] += sz[v];
  }
  f[u] += sz[u];
}
void Dp(int u, int fa) {
  for (int v : e[u]) {
    if (v == fa)
      continue;
    g[v] = g[u] - sz[v] + n - sz[v];
    Dp(v, u);
  }
}
int Solve() {
  Dfs(1, 0), g[1] = f[1];
  Dp(1, 0);
  cout << *max_element(g + 1, g + n + 1) << "\n";
  return 0;
}
} // namespace Tree
namespace Ring {
const int NN = 7505;
int num, dfn[N], pr[N];
bool inr[N];
int f[N], g[N], mxg[N], sz[N], sf[N];
int len, tot, d[N], psz[N], dp[NN][NN];
vector<int> ring;
void Dfs(int u, int fa) {
  dfn[u] = ++num, pr[u] = fa;
  for (int v : e[u]) {
    if (v == fa)
      continue;
    if (!dfn[v])
      Dfs(v, u);
    else if (dfn[u] < dfn[v]) {
      for (int i = v;; i = pr[i]) {
        inr[i] = 1, ring.push_back(i);
        if (i == u)
          break;
      }
    }
  }
}
void Dfs2(int u, int fa) {
  sz[u] = 1;
  for (int v : e[u]) {
    if (v == fa || inr[v])
      continue;
    Dfs2(v, u);
    f[u] += f[v];
    sz[u] += sz[v];
  }
  f[u] += sz[u];
}
void Dfs3(int u, int fa) {
  if (fa)
    g[u] += n - sz[u];
  int sum = 0;
  for (int v : e[u]) {
    if (v == fa || inr[v])
      continue;
    sum += f[v];
  }
  for (int v : e[u]) {
    if (v == fa || inr[v])
      continue;
    g[v] = g[u] + sum - f[v];
    Dfs3(v, u);
    mxg[u] = max(mxg[u], mxg[v]);
  }
  sf[u] = sum, g[u] += n + sum;
  mxg[u] = max(mxg[u], g[u]);
}
inline int Dis(int i) { return d[i + 1] - d[i] - 1; }
inline int F(int n, int k) { return (n + n - k + 1) * k / 2; }
int Dp(int l, int r) {
  if ((l == 1 && r == tot) || (l > r && r + 1 == l))
    return 0;
  int &ans = dp[l][r];
  if (ans > 0)
    return ans;
  auto pr = [&](int l) { return l == 1 ? tot : l - 1; };
  auto nx = [&](int r) { return r == tot ? 1 : r + 1; };
  int pl = pr(l), nr = nx(r);
  int st = n -
           (l <= r ? psz[r] - psz[l - 1] + d[r] - d[l] + 1 - (r - l + 1)
                   : psz[r + tot] - psz[l - 1] + d[r + tot] - d[l] + 1 -
                         (r + tot - l + 1)) -
           Dis(pl) - Dis(r);
  // if(l <= r)cerr << "st = " << n << "-" << (psz[r] - psz[l - 1] + d[r] - d[l]
  // + 1 - (r - l + 1) ) << "-" << Dis(pl) << "-" << Dis(r) << "\n"; else cerr
  // << "st = " << n << "-" << psz[r + tot] - psz[l - 1] + d[r + tot] - d[l] + 1
  // - (r + tot - l + 1) << "-" << Dis(pl) << "-" << Dis(r) << "\n";
  int dl = pl == nr ? 0 : Dis(pr(pl));
  int dr = pl == nr ? 0 : Dis(nr);
  ans = max(Dp(pl, r) + st + F(st - (psz[pl] - psz[pl - 1]), dl),
            Dp(l, nr) + st + F(st - (psz[nr] - psz[nr - 1]), dr));
  // cerr << st << " +max " << Dp(pl , r) << "+" << F(st - (psz[pl] - psz[pl -
  // 1]) , dl) << " , " << Dp(l , nr) << '+' << F(st - (psz[nr] - psz[nr - 1]) ,
  // dr) << "\n"; cerr << "dp[" << l << ',' << r << "]:" << ans << "; " << pl <<
  // ',' << nr << ' ' << st << "\n";
  return ans;
}
int Solve() {
  Dfs(1, 0);
  for (int u : ring)
    Dfs2(u, 0), Dfs3(u, 0);
  len = ring.size(), tot = 0;
  if (len == n) {
    cout << n * (n + 1) / 2 << "\n";
    return 0;
  }
  for (int i = 0; i < len; i++) {
    int u = ring[i];
    if (sz[u] == 1)
      continue;
    d[++tot] = i;
    psz[tot] = psz[tot - 1] + sz[u];
  }
  // for(int u : ring)cerr << u << ",";
  // cerr << "\n";
  // for(int i = 1 ; i <= n ; i++)
  // 	cerr << i << ":" << sz[i] << " " << f[i] << " " << g[i] << ' ' << mxg[i]
  // << "\n"; cerr << tot << ":"; for(int i = 1 ; i <= tot ; i++) 	cerr <<
  // '(' << d[i] << "," << ring[d[i]] << ")" << " \n"[i == tot];
  d[0] = d[tot] - len;
  for (int i = tot + 1; i <= tot * 2; i++) {
    int u = ring[d[i - tot]];
    psz[i] = psz[i - 1] + sz[u];
    d[i] = d[i - tot] + len;
  }
  int ans = 0, ss = 0;
  for (int u : ring)
    ss += sf[u];
  for (int j = 0, i = 0; j < len; j++) {
    int u = ring[j];
    if (sz[u] == 1) {
      auto pr = [&](int l) { return l == 1 ? tot : l - 1; };
      auto nx = [&](int r) { return r == tot ? 1 : r + 1; };
      int l = i ? i : tot, r = i == tot ? 1 : i + 1;
      int tmp = ss + F(n, Dis(l) + 1);
      if (tot > 1) {
        // cerr << "j = " << j << ',' << u << " " << l << ',' << r << ":\n";
        // cerr << Dp(l , l) << "+" << tmp << "+" << F(n - Dis(l) - (psz[l] -
        // psz[l - 1]) , Dis(pr(l))) << "\n"; cerr << Dp(r , r) << "+" << tmp <<
        // "+" << F(n - Dis(l) - (psz[r] - psz[r - 1]) , Dis(r)) << "\n";
        ans = max(ans, Dp(l, l) + tmp +
                           F(n - Dis(l) - (psz[l] - psz[l - 1]), Dis(pr(l))));
        ans = max(ans, Dp(r, r) + tmp +
                           F(n - Dis(l) - (psz[r] - psz[r - 1]), Dis(r)));
      } else {
        // cerr << Dp(l , l) << "+" << ss << "+F(" << n << ',' << Dis(l) + 1 <<
        // ")" << F(n , Dis(l) + 1) << "\n";
        ans = max(ans, Dp(l, l) + tmp);
      }
    } else {
      ++i;
      int dis = tot == 1 ? Dis(i) : Dis(i - 1) + Dis(i);
      // cerr << u << ":" << Dp(i , i) << "+" << "F(" << n - sz[u] << ',' << dis
      // << ")"
      // 	<<  F(n - sz[u] , dis) << "+" << mxg[u] << "+" << ss - sf[u] <<
      // "\n";
      ans = max(ans, Dp(i, i) + F(n - sz[u], dis) + mxg[u] + ss - sf[u]);
    }
  }
  cout << ans << "\n";
  return 0;
}
} // namespace Ring
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n;
  m = n;
  for (int i = 1; i <= m; i++) {
    int u, v;
    cin >> u >> v;
    u++, v++;
    e[u].push_back(v);
    e[v].push_back(u);
  }
  if (m == n - 1)
    Tree::Solve();
  else
    Ring::Solve();
  return 0;
}