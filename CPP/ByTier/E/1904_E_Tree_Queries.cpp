// Problem: CF 1904 E - Tree Queries
// https://codeforces.com/contest/1904/problem/E

/*
 * Problem: E. Tree Queries
 * 
 * Algorithms/Techniques:
 * - Heavy Light Decomposition (HLD) for tree traversal and path queries
 * - Segment Tree with range queries for efficient path length computation
 * - LCA (Lowest Common Ancestor) and distance calculations in tree
 * - Efficient handling of queries with node removals
 * 
 * Time Complexity: O((n + q) * log^2(n)) where n is number of nodes, q is number of queries
 * Space Complexity: O(n * log(n)) for HLD and segment tree structures
 */

#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <functional>
#include <initializer_list>
#include <tuple>
#include <utility>
#include <vector>

#pragma GCC optimize(2)
using namespace std;
namespace Fread {
const int SIZE = 1 << 19;
char buf[SIZE], *S, *T;
inline char getchar() {
  if (S == T) {
    T = (S = buf) + fread(buf, 1, SIZE, stdin);
    if (S == T)
      return '\n';
  }
  return *S++;
}
} // namespace Fread
namespace Fwrite {
const int SIZE = 1 << 17;
char buf[SIZE], *S = buf, *T = buf + SIZE;
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
namespace Fastio {
struct Reader {
  template <typename T> Reader &operator>>(T &x) {
    x = 0;
    char c = getchar();
    while (c < '0' || c > '9')
      c = getchar();
    while (c >= '0' && c <= '9') {
      x = x * 10 + (c - '0');
      c = getchar();
    }
    return *this;
  }
} cin;
struct Writer {
  template <typename T> Writer &operator<<(T x) {
    if (x == 0) {
      putchar('0');
      return *this;
    }
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
} // namespace Fastio
#define cin Fastio ::cin
#define cout Fastio ::cout
struct HLD {
  int n, tot = 0, idx = 0;
  vector<vector<int>> e;
  vector<int> hd, ver, nxt, sz, pa, dep, hc, top, l, r, id;
  void init(int n) {
    nxt.resize(2 * n);
    ver = nxt;
    sz.resize(n + 1);
    hd = id = r = l = top = hc = dep = pa = sz;
  }
  void add(int u, int v) {
    ver[++tot] = v;
    nxt[tot] = hd[u];
    hd[u] = tot;
  }
  void prep(int root = 1) {
    dfs1(root, 0);
    dfs2(root, root);
  }
  void dfs1(int u, int f) {
    sz[u] = 1;
    pa[u] = f;
    dep[u] = dep[f] + 1;
    for (int i = hd[u]; i; i = nxt[i]) {
      int v = ver[i];
      if (v == f)
        continue;
      dfs1(v, u);
      sz[u] += sz[v];
      if (sz[v] > sz[hc[u]])
        hc[u] = v;
    }
  }
  void dfs2(int u, int t) {
    top[u] = t;
    l[u] = ++idx;
    id[idx] = u;
    if (hc[u])
      dfs2(hc[u], t);
    for (int i = hd[u]; i; i = nxt[i]) {
      int v = ver[i];
      if (v == hc[u] || v == pa[u])
        continue;
      dfs2(v, v);
    }
    r[u] = idx;
  }
  int lca(int u, int v) {
    while (top[u] != top[v])
      if (dep[top[u]] < dep[top[v]])
        v = pa[top[v]];
      else
        u = pa[top[u]];
    return dep[u] < dep[v] ? u : v;
  }
  int dist(int u, int v) { return dep[u] + dep[v] - 2 * dep[lca(u, v)]; }
  bool isAncester(int u, int v) { return l[u] <= l[v] && r[v] <= r[u]; }
  int jump(int u, int k) {
    int d = dep[u] - k;
    while (dep[top[u]] > d)
      u = pa[top[u]];
    return id[l[u] - dep[u] + d];
  }
} h;
struct Info {
  int l, r;
};
Info operator+(const Info &a, const Info &b) {
  int d1 = h.dist(a.l, a.r), d2 = h.dist(b.l, b.r);
  // Select maximum distance from the four possible combinations
  auto t = (d1 > d2) ? make_pair(d1, make_pair(a.l, a.r)) : make_pair(d2, make_pair(b.l, b.r));
  for (auto x : {a.l, a.r})
    for (auto y : {b.l, b.r})
      if (h.dist(x, y) > t.first)
        t = make_pair(h.dist(x, y), make_pair(x, y));
  auto segm = t.second;
  return {segm.first, segm.second};
}
struct SegmentTree {
  int n;
  vector<Info> info;
  void init(int len) {
    n = len;
    int e = ceil(log2(n)) + 1;
    info.resize(1 << e);
    function<void(int, int, int)> build = [&](int u, int l, int r) {
      if (l == r)
        info[u] = {h.id[l], h.id[l]};
      else {
        int m = l + r >> 1;
        build(u << 1, l, m), build(u << 1 | 1, m + 1, r);
        pull(u);
      }
    };
    build(1, 1, n);
  }
  void pull(int u) { info[u] = info[u << 1] + info[u << 1 | 1]; }
  Info query(int u, int l, int r, int x, int y) {
    if (x <= l && r <= y)
      return info[u];
    int m = l + r >> 1;
    if (y <= m)
      return query(u << 1, l, m, x, y);
    if (x > m)
      return query(u << 1 | 1, m + 1, r, x, y);
    return query(u << 1, l, m, x, y) + query(u << 1 | 1, m + 1, r, x, y);
  }
  Info query(int l, int r) { return query(1, 1, n, l, r); }
} seg;
#define fore(i, n) for (int i = 1; i <= n; i++)
#define pb push_back
int main() {
  int n, q;
  cin >> n >> q;
  h.init(n);
  fore(i, n - 1) {
    int u, v;
    cin >> u >> v;
    h.add(u, v);
    h.add(v, u);
  }
  h.prep();
  seg.init(n);
  fore(i, q) {
    int x, k, y;
    cin >> x >> k;
    Info ans{x, x};
    vector<pair<int, int>> v;
    fore(j, k) {
      cin >> y;
      if (h.isAncester(y, x)) {
        // If y is an ancestor of x, calculate subranges that exclude y's subtree
        int z = h.jump(x, h.dep[x] - h.dep[y] - 1);
        int s = h.l[z], e = h.r[z];
        if (s - 1 >= 1)
          v.pb({1, s - 1});
        if (e + 1 <= n)
          v.pb({e + 1, n});
      } else
        // Add the entire subtree of y to excluded ranges
        v.pb({h.l[y], h.r[y]});
    }
    sort(v.begin(), v.end());
    int r = 0;
    for (auto t : v) {
      int a, b;
      tie(a, b) = t;
      if (r + 1 <= a - 1)
        ans = ans + seg.query(r + 1, a - 1);
      r = max(r, b);
    }
    if (r + 1 <= n)
      ans = ans + seg.query(r + 1, n);
    cout << max(h.dist(x, ans.l), h.dist(x, ans.r)) << '\n';
  }
}


// https://github.com/VaHiX/CodeForces/