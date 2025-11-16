// Problem: CF 1967 D - Long Way to be Non-decreasing
// https://codeforces.com/contest/1967/problem/D

/*
Algorithm: 
- This problem uses a combination of topological sorting and binary search to find the minimum number of operations.
- First, build a directed graph based on array b where each node points to its image under b.
- Use topological sorting to process nodes in order, identifying cycles.
- For each cycle, compute the length of the cycle and assign id and bel values for each node.
- Use binary search on the answer (number of operations) and for each candidate, check if it's feasible using a greedy approach.
- The check function uses the cycle information and topological ordering to determine if the array can be made non-decreasing.

Time Complexity: O(n + m + n log n)
Space Complexity: O(n + m)

Techniques:
1. Topological sorting for cycle detection and processing
2. Binary search on the answer
3. Cycle detection and computation of cycle lengths
4. Greedy checking during binary search
*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#include <utility>

#define fi first
#define se second
#define pb push_back
#define y1 hsduaishxu
#define mkp make_pair
using namespace std;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
typedef pair<int, ll> pil;
typedef pair<ll, ll> pll;
typedef unsigned int uint;
typedef vector<pii> vpii;
const int maxn = 1000005;
const ll mod = 998244353;
inline int Min(int x, int y) { return x < y ? x : y; }
inline int Max(int x, int y) { return x > y ? x : y; }
inline ll Min(ll x, ll y) { return x < y ? x : y; }
inline ll Max(ll x, ll y) { return x > y ? x : y; }
inline void ad(int &x, int y, int z) {
  x = y + z;
  if (x >= mod)
    x -= mod;
}
inline void ad(ll &x, ll y, ll z) {
  x = y + z;
  if (x >= mod)
    x -= mod;
}
inline void ad(int &x, int y) {
  x += y;
  if (x >= mod)
    x -= mod;
}
inline void ad(int &x, ll y) {
  x += y;
  if (x >= mod)
    x -= mod;
}
inline void ad(ll &x, ll y) {
  x += y;
  if (x >= mod)
    x -= mod;
}
inline void siu(int &x, int y, int z) {
  x = y - z;
  if (x < 0)
    x += mod;
}
inline void siu(int &x, int y) {
  x -= y;
  if (x < 0)
    x += mod;
}
inline void siu(ll &x, ll y) {
  x -= y;
  if (x < 0)
    x += mod;
}
inline ll myabs(ll x) { return x < 0 ? -x : x; }
inline void tmn(int &x, int y) {
  if (y < x)
    x = y;
}
inline void tmx(int &x, int y) {
  if (y > x)
    x = y;
}
inline void tmn(ll &x, ll y) {
  if (y < x)
    x = y;
}
inline void tmx(ll &x, ll y) {
  if (y > x)
    x = y;
}
ll qpow(ll aa, ll bb) {
  ll res = 1;
  while (bb) {
    if (bb & 1)
      res = res * aa % mod;
    aa = aa * aa % mod;
    bb >>= 1;
  }
  return res;
}
ll qpow(ll aa, ll bb, ll md) {
  ll res = 1;
  while (bb) {
    if (bb & 1)
      res = res * aa % md;
    aa = aa * aa % md;
    bb >>= 1;
  }
  return res;
}
inline ll Inv(ll x) { return qpow(x, mod - 2); }
int _, __;
int n, m;
int a[maxn], p[maxn];
int d[maxn];
queue<int> q;
int dep[maxn], siz[maxn], dfscnt, dfn[maxn];
vector<int> g[maxn];
bool vs[maxn];
int st[maxn], tp, id[maxn], len[maxn], bel[maxn];
void dfs(int u) {
  dfn[u] = ++dfscnt;
  siz[u] = 1;
  for (auto v : g[u]) {
    dep[v] = dep[u] + 1;
    dfs(v);
    siz[u] += siz[v];
  }
}
bool ck(int x, int y, int k) {
  if (bel[x] != bel[y])
    return 0;
  if (!d[y])
    return dfn[x] >= dfn[y] && dfn[x] < dfn[y] + siz[y] && dep[x] <= dep[y] + k;
  int t = k - dep[x], l = len[y];
  x = id[x];
  y = id[y];
  return t >= (y - x + l) % l;
}
bool chk(int x) {
  int nw = 0;
  for (int i = 1; i <= n; i++) {
    while (nw < m && ck(a[nw + 1], i, x))
      nw++;
  }
  return nw == m;
}
void solve() {
  cin >> m >> n; // Read input (note: swapped m and n vs input format, but kept correct parsing)
  for (int i = 1; i <= m; i++)
    cin >> a[i];
  for (int i = 1; i <= n; i++)
    d[i] = vs[i] = dep[i] = siz[i] = dfn[i] = bel[i] = 0, g[i].clear();
  for (int i = 1; i <= n; i++)
    cin >> p[i], d[p[i]]++;
  while (!q.empty())
    q.pop();
  for (int i = 1; i <= n; i++)
    if (!d[i])
      q.push(i);
  tp = 0;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    st[++tp] = u;
    d[p[u]]--;
    vs[u] = 1;
    if (!d[p[u]])
      q.push(p[u]);
  }
  for (int i = 1; i <= n; i++)
    if (!vs[i])
      id[i] = i;
  for (int i = tp; i >= 1; i--)
    id[st[i]] = id[p[st[i]]], g[p[st[i]]].push_back(st[i]);
  dfscnt = 0;
  for (int i = 1; i <= n; i++)
    if (!vs[i])
      dfs(i);
  for (int i = 1; i <= n; i++)
    if (!vs[i]) {
      int u = i;
      int t = 0;
      while (1) {
        id[u] = t++;
        bel[u] = i;
        vs[u] = 1;
        u = p[u];
        if (u == i)
          break;
      }
      u = i;
      while (1) {
        len[u] = t;
        u = p[u];
        if (u == i)
          break;
      }
    }
  for (int u = 1; u <= n; u++)
    if (!d[u])
      len[u] = len[id[u]], bel[u] = bel[id[u]], id[u] = id[id[u]];
  int l = 0, r = n, res = -1;
  while (l <= r) {
    int mid = (l + r) >> 1;
    if (chk(mid))
      res = mid, r = mid - 1;
    else
      l = mid + 1;
  }
  cout << res << "\n";
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  _ = 1;
  cin >> _;
  while (_--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/