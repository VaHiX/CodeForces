// Problem: CF 1916 E - Happy Life in University
// https://codeforces.com/contest/1916/problem/E

/*
 * Problem: E. Happy Life in University
 *
 * Algorithm:
 * - Build a tree from input and use DFS with segment tree to compute max f(u,v)
 * = diff(u,lca(u,v)) * diff(v,lca(u,v))
 * - For each node, maintain a segment tree to track how many unique activities
 * exist along paths from that node to root.
 * - Use a technique similar to heavy-light decomposition with interval updates
 * and queries.
 *
 * Time Complexity: O(n log n) per test case (due to segment tree operations and
 * DFS traversal) Space Complexity: O(n) for storing the tree and auxiliary
 * structures.
 */

#include <algorithm>
#include <cmath>
#include <ctype.h>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;
namespace Fread {
const int SZ = 1 << 18;
char buf[SZ], *S, *T;
inline char getchar() {
  if (S == T) {
    T = (S = buf) + fread(buf, 1, SZ, stdin);
    if (S == T)
      return '\n';
  }
  return *S++;
}
} // namespace Fread
namespace Fwrite {
const int SZ = 1 << 12;
char buf[SZ], *S = buf, *T = buf + SZ;
inline void flush() {
  fwrite(buf, 1, S - buf, stdout);
  S = buf;
}
inline void putchar(char c) {
  *S++ = c;
  if (S == T)
    flush();
}
struct NTR {
  ~NTR() { flush(); }
} ztr;
} // namespace Fwrite
#define getchar Fread ::getchar
#define putchar Fwrite ::putchar
namespace Fast {
struct Reader {
  template <typename T> Reader &operator>>(T &x) {
    char c = getchar();
    while (!isdigit(c))
      c = getchar();
    x = 0;
    while (isdigit(c))
      x = x * 10 + (c - '0'), c = getchar();
    return *this;
  }
} cin;
struct Writer {
  template <typename T> Writer &operator<<(T x) {
    static int sta[45];
    int top = 0;
    while (x) {
      sta[++top] = x % 10;
      x /= 10;
    }
    while (top) {
      putchar(sta[top] + '0');
      --top;
    }
    return *this;
  }
  Writer &operator<<(char c) {
    putchar(c);
    return *this;
  }
} cout;
} // namespace Fast
#define cin Fast ::cin
#define cout Fast ::cout
#define fore(i, L, R) for (int i = L; i <= R; i++)
const int MN = 3e5 + 1;
typedef long long ll;
ll ans;
int T, n, tot, nL, ts;
vector<int> pa, hd, nxt, ver, ispa, val, mx, tag, tI, tO;
basic_string<int> pos[MN], same[MN];
void adde(int u, int v) {
  ver[++tot] = v;
  nxt[tot] = hd[u];
  hd[u] = tot;
}
inline void pushup(int u) { mx[u] = max(mx[u << 1], mx[u << 1 | 1]); }
inline void add(int u, int v) { tag[u] += v, mx[u] += v; }
inline void pushdown(int u) {
  if (tag[u]) {
    add(u << 1, tag[u]);
    add(u << 1 | 1, tag[u]);
    tag[u] = 0;
  }
}
inline void modify(int u, int l, int r, int x, int y, int v = 1) {
  if (x > r || y < l)
    return;
  if (x <= l && r <= y) {
    add(u, v);
    return;
  }
  int mid = (l + r) >> 1;
  pushdown(u);
  modify(u << 1, l, mid, x, y, v), modify(u << 1 | 1, mid + 1, r, x, y, v);
  pushup(u);
}
inline int qMax(int u, int l, int r, int x, int y) {
  if (x > r || y < l)
    return 0;
  if (x <= l && r <= y)
    return mx[u];
  int mid = (l + r) >> 1;
  pushdown(u);
  return max(qMax(u << 1, l, mid, x, y), qMax(u << 1 | 1, mid + 1, r, x, y));
}
inline void dfs(int u, int fa) {
  int cur = val[u];
  if (!pos[cur].empty())
    same[pos[cur].back()].push_back(u);
  if (!ispa[u]) {
    tI[u] = tO[u] = ++ts;
    modify(1, 1, nL, ts, ts);
    return;
  }
  pos[cur].push_back(u);
  for (int i = hd[u]; i; i = nxt[i]) {
    int v = ver[i];
    dfs(v, u);
    if (!tI[u])
      tI[u] = tI[v];
    tO[u] = tO[v];
  }
  while (!same[u].empty()) {
    int v = same[u].back();
    same[u].pop_back();
    modify(1, 1, nL, tI[v], tO[v], -1);
  }
  pos[cur].pop_back();
  modify(1, 1, nL, tI[u], tO[u]);
  int mx1 = 1, mx2 = 0;
  for (int i = hd[u]; i; i = nxt[i]) {
    int v = ver[i];
    int cnt = qMax(1, 1, nL, tI[v], tO[v]);
    if (cnt > mx1)
      mx2 = mx1, mx1 = cnt;
    else if (cnt > mx2)
      mx2 = cnt;
  }
  [](ll &x, ll y) { x = (x > y ? x : y); }(ans, 1ll * mx1 * mx2);
}
inline void solve() {
  cin >> n;
  hd.resize(n + 1);
  ver = nxt = pa = ispa = val = tO = tI = hd;
  fore(i, 2, n) cin >> pa[i], adde(pa[i], i), ispa[pa[i]] = 1;
  fore(i, 1, n) nL += ispa[i];
  nL = n - nL;
  int exp = ceil(log2(nL)), tt = 1 << (exp + 1);
  mx.resize(tt), tag = mx;
  fore(i, 1, n) cin >> val[i];
  dfs(1, 0);
  cout << ans << '\n';
  if (T) {
    ans = 1;
    tot = nL = ts = 0;
    hd.clear();
    mx.clear();
  }
}
int main() {
  cin >> T;
  while (T--)
    solve();
}

// https://github.com/VaHiX/CodeForces/