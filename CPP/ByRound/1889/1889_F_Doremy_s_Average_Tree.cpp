// Problem: CF 1889 F - Doremy's Average Tree
// https://codeforces.com/contest/1889/problem/F

/*
Algorithm: Tree DFS traversal with greedy approach to minimize lexicographically.
Techniques:
- Tree DFS for subtree size calculation and ancestor tracking.
- Greedy selection of nodes for operation to minimize values.
- Fraction comparison for handling averages without floating point errors.
Time Complexity: O(n^2) per test case, due to nested loops over nodes and ancestors.
Space Complexity: O(n) for storing tree structure, DFS information, and auxiliary arrays.
*/

#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>

#define Spc putchar(' ')
#define End putchar('\n')
#define For(i, il, ir) for (int i = (il); i <= (ir); ++i)
#define Fr(i, il, ir) for (int i = (il); i < (ir); ++i)
#define Forr(i, ir, il) for (int i = (ir); i >= (il); --i)
#define ForE(u) for (int i = head[u]; ~i; i = e[i].nxt)
#define fi first
#define se second
#define mk make_pair
#define pb emplace_back
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
namespace _TvT_ {
template <typename T> inline void rd(T &x) {
  bool f = 0;
  x = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      f = 1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9')
    x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
  if (f)
    x = -x;
}
template <typename T, typename... Args> void rd(T &first, Args &...args) {
  rd(first), rd(args...);
}
int write_num[50];
template <typename T> inline void write(T x) {
  int len = 0;
  if (x < 0)
    putchar('-'), x = -x;
  do
    write_num[len++] = x % 10ll;
  while (x /= 10ll);
  while (len--)
    putchar(write_num[len] + '0');
}
template <typename T, typename... Args> void write(T first, Args... args) {
  write(first), Spc, write(args...);
}
} // namespace _TvT_
using namespace _TvT_;
const int maxn = 5005;
struct frac {
  ll x, y;
  frac(ll xx = 0, ll yy = 0) { x = xx, y = yy; }
};
frac operator+(frac A, frac B) { return frac(A.x + B.x, A.y + B.y); }
bool operator<(frac A, frac B) { return A.x * B.y < B.x * A.y; }
bool operator==(frac A, frac B) { return A.x * B.y == B.x * A.y; }
int n, rt, K;
vector<int> ve[maxn];
bool ban[maxn], used[maxn];
int sz[maxn], fa[maxn];
int seq[maxn], dfn[maxn], timer;
frac val[maxn], ave[maxn], res[maxn];
void dfs(int u, int ff) {
  dfn[u] = ++timer, seq[timer] = u;
  fa[u] = ff, sz[u] = 1;
  for (auto v : ve[u])
    if (v ^ ff)
      dfs(v, u), ave[u] = ave[u] + ave[v], sz[u] += sz[v];
}
void case1(int u) {
  if (!K)
    return;
  frac mn = val[u];
  int mnid = u;
  for (int i = u; i; i = fa[i])
    if (!ban[i] && !(mn < ave[i]))
      mn = ave[i], mnid = i;
  if (mn == val[u])
    return;
  K--, used[mnid] = true, res[u] = mn;
}
void case2(int u, int anc) {
  int lft = K + 1;
  bool flag = true;
  vector<int> tmp;
  for (int i = dfn[anc]; i < dfn[anc] + sz[anc]; i++) {
    int v = seq[i];
    if (!(v < u && res[v] < val[v]))
      continue;
    int rep = 0;
    for (int i = v; i; i = fa[i])
      if (!(dfn[u] >= dfn[i] && dfn[u] <= dfn[i] + sz[i] - 1))
        if (!ban[i])
          rep = i;
    if (!rep || --lft < 0) {
      res[u] = ave[anc];
      return;
    }
    tmp.pb(rep);
    i = dfn[rep] + sz[rep] - 1;
  }
  frac mn = val[u];
  int mnid = 0;
  if (lft)
    for (int i = u; i; i = fa[i])
      if (!ban[i] && !(mn < ave[i]))
        mn = ave[i], mnid = i;
  if (!(mn < ave[anc])) {
    res[u] = ave[anc];
    return;
  }
  if (mn == val[u])
    mnid = 0;
  res[u] = mn, used[anc] = false, K = lft;
  for (int i : tmp)
    used[i] = true;
  if (mnid)
    used[mnid] = true, K--;
}
void solve() {
  rd(n, rt, K);
  For(i, 1, n) rd(val[i].x), val[i].y = 1, ave[i] = res[i] = val[i];
  For(i, 2, n) {
    int u, v;
    rd(u, v);
    ve[u].pb(v), ve[v].pb(u);
  }
  dfs(rt, 0);
  For(u, 1, n) {
    int tp = 0;
    for (int i = u; i; i = fa[i])
      if (used[i])
        tp = i;
    if (!tp)
      case1(u);
    else
      case2(u, tp);
    for (int i = u; i; i = fa[i])
      if (res[u] < ave[i])
        ban[i] = true;
  }
  int resnum = 0;
  For(i, 1, n) if (used[i]) resnum++;
  write(resnum), End;
  For(i, 1, n) if (used[i]) write(i), Spc;
  End;
  timer = 0;
  For(i, 1, n) ban[i] = used[i] = false, fa[i] = 0, ve[i].clear();
}
signed main() {
  int T;
  rd(T);
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/