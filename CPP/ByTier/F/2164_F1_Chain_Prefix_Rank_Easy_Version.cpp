// Problem: CF 2164 F1 - Chain Prefix Rank (Easy Version)
// https://codeforces.com/contest/2164/problem/F1

/*
 * Problem: Chain Prefix Rank (Easy Version)
 *
 * Algorithm: This solution uses a combination of tree traversal, Treap (self-balancing BST),
 *            and dynamic programming on a tree to count valid permutations satisfying the ancestor
 *            condition. It processes the tree depth-first, maintaining a Treap to keep track of
 *            rank information, and uses DP to accumulate counts.
 *
 * Time Complexity: O(n^2) in worst case due to operations on Treap and graph traversal,
 *                  but optimized in practice due to tree properties.
 * Space Complexity: O(n) for storing tree structure, Treap nodes, DP table, and auxiliary arrays.
 */

#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;
const int N = 5E5 + 5;
const ll mod = 998244353ll;
int p[N], fa[N], fac[N], inv[N];
vector<int> G[N], Gx[N];
set<int> in[N], out[N];
map<pair<int, int>, ll> dp, val;
int l[N], r[N], rt, h[N], tot, dat[N], siz[N];
int inline BF(int &rt) { return h[l[rt]] - h[r[rt]]; }
inline void flush(int &rt) {
  h[rt] = max(h[l[rt]], h[r[rt]]) + 1;
  siz[rt] = siz[l[rt]] + siz[r[rt]] + 1;
}
inline void zig(int &rt) {
  int rc = r[rt];
  r[rt] = l[rc];
  l[rc] = rt;
  flush(rt), flush(rc);
  rt = rc;
}
inline void zag(int &rt) {
  int lc = l[rt];
  l[rt] = r[lc];
  r[lc] = rt;
  flush(rt), flush(lc);
  rt = lc;
}
inline bool isLL(int &rt) { return BF(rt) > 1 && BF(l[rt]) >= 0; }
inline bool isLR(int &rt) { return BF(rt) > 1 && BF(l[rt]) < 0; }
inline bool isRR(int &rt) { return BF(rt) < -1 && BF(r[rt]) <= 0; }
inline bool isRL(int &rt) { return BF(rt) < -1 && BF(r[rt]) > 0; }
void insert(int &rt, int v, int rnk) {
  if (rt == 0) {
    rt = ++tot, dat[rt] = v, siz[rt] = 1, h[rt] = 1;
    return;
  }
  if (rnk <= siz[l[rt]] + 1)
    insert(l[rt], v, rnk);
  else
    insert(r[rt], v, rnk - siz[l[rt]] - 1);
  flush(rt);
  if (isLL(rt))
    zag(rt);
  else if (isLR(rt))
    zig(l[rt]), zag(rt);
  else if (isRR(rt))
    zig(rt);
  else if (isRL(rt))
    zag(r[rt]), zig(rt);
}
void erase(int &rt, int v) {
  if (!rt)
    return;
  if (v == siz[l[rt]] + 1) {
    if (l[rt] == 0)
      rt = r[rt];
    else if (r[rt] == 0)
      rt = l[rt];
    else {
      int nx = r[rt];
      while (l[nx])
        nx = l[nx];
      erase(r[rt], 1);
      l[nx] = l[rt], r[nx] = r[rt];
      rt = nx;
    }
  }
  if (v <= siz[l[rt]])
    erase(l[rt], v);
  if (v > siz[l[rt]] + 1)
    erase(r[rt], v - siz[l[rt]] - 1);
  if (!rt)
    return;
  flush(rt);
  if (isLL(rt))
    zag(rt);
  else if (isLR(rt))
    zig(l[rt]), zag(rt);
  else if (isRR(rt))
    zig(rt);
  else if (isRL(rt))
    zag(r[rt]), zig(rt);
}
int RankToVal(int &rt, int v) {
  if (rt == 0)
    return 0;
  if (v <= siz[l[rt]])
    return RankToVal(l[rt], v);
  else if (v == siz[l[rt]] + 1)
    return dat[rt];
  else
    return RankToVal(r[rt], v - siz[l[rt]] - 1);
}
ll Inv(ll x) {
  ll tmp = x, res = 1, t = mod - 2;
  while (t) {
    if (t & 1)
      res = res * tmp % mod;
    tmp = tmp * tmp % mod, t >>= 1;
  }
  return res;
}
void dfs(int u, int dep) {
  int s = RankToVal(rt, p[u]);
  int t = RankToVal(rt, p[u] + 1);
  out[s].insert(u), in[u].insert(s), out[u].insert(t), in[t].insert(u);
  pair<int, int> P = make_pair(s, u), Q = make_pair(u, t);
  dp[P] = dp[Q] = 1, val[P] = val[Q] = 0;
  Gx[s].push_back(u), Gx[u].push_back(t);
  insert(rt, u, p[u] + 1);
  for (auto v : G[u])
    dfs(v, dep + 1);
  erase(rt, p[u] + 1);
}
void solve() {
  dp.clear(), val.clear();
  int n;
  rt = 0;
  cin >> n;
  for (int i = 0; i <= n + 1; i++)
    G[i].clear(), Gx[i].clear(), l[i] = r[i] = h[i] = dat[i] = siz[i] = 0,
                                 in[i].clear(), out[i].clear();
  fac[0] = inv[0] = 1ll;
  for (ll i = 1; i <= n; i++) {
    fac[i] = fac[i - 1] * i % mod;
    inv[i] = Inv(fac[i]);
  }
  Gx[0].push_back(n + 1);
  out[0].insert(n + 1), in[n + 1].insert(0);
  pair<int, int> tmp = make_pair(0, n + 1);
  dp[tmp] = 1, val[tmp] = 0;
  fa[n + 1] = 0, fa[1] = n + 1, p[0] = 0, p[n + 1] = 1;
  for (int i = 2; i <= n; i++)
    cin >> fa[i], G[fa[i]].push_back(i);
  for (int i = 1; i <= n; i++)
    cin >> p[i], p[i]++;
  insert(rt, 0, 1), insert(rt, n + 1, 2);
  dfs(1, 0);
  queue<int> q;
  for (int i = 1; i <= n; i++) {
    if (in[i].size() == 1 && out[i].size() == 1)
      q.push(i);
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    int s = *in[u].begin(), t = *out[u].begin();
    in[u].clear(), out[u].clear();
    pair<int, int> P = make_pair(s, u), Q = make_pair(u, t),
                   R = make_pair(s, t);
    dp[R] = dp[R] * dp[P] % mod * dp[Q] % mod *
            fac[val[P] + val[Q] + val[R] + 1] % mod * inv[val[R]] % mod *
            inv[val[P] + val[Q] + 1] % mod;
    val[R] = val[R] + val[P] + val[Q] + 1;
    out[s].erase(u), in[t].erase(u);
    if (out[s].size() == 1 && in[s].size() == 1)
      q.push(s);
    if (out[t].size() == 1 && in[t].size() == 1)
      q.push(t);
  }
  cout << dp[make_pair(0, n + 1)] << '\n';
}
int main() {
  ios ::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int T = 1;
  cin >> T;
  while (T--)
    solve();
}


// https://github.com/VaHiX/CodeForces/