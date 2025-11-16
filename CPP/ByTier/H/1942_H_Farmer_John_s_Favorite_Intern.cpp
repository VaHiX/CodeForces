// Problem: CF 1942 H - Farmer John's Favorite Intern
// https://codeforces.com/contest/1942/problem/H

/*
 * Code Purpose: This code solves the problem of maintaining a peach tree (a rooted tree with nodes having peaches)
 * where operations involve growing or harvesting peaches on nodes, with the goal being to determine if
 * the tree can remain healthy (each node has at least the required number of peaches) after each prefix of operations.
 * 
 * Techniques Used:
 * - Heavy-Light Decomposition (HLD) on tree to efficiently handle subtree operations
 * - Segment Tree with Matrix operations to track maximum values
 * - Lazy Propagation with prefix sums to represent cumulative effects
 *
 * Time Complexity: O((n + q) * log^2(n)) per test case
 * Space Complexity: O(n * log^2(n)) due to the segment trees and HLD structures
 */

#include <stdio.h>
#include <algorithm>

namespace FastRead {
char buf[1000005], *s = buf, *t = buf;
#define gc()                                                                   \
  s == t && (t = (s = buf) + fread(buf, 1, 1000000, stdin), s == t) ? EOF : *s++
template <typename T> inline void Read(T &x) {
  x = 0;
  int f = 0;
  char ch = gc();
  while (ch < '0' || ch > '9')
    f = ch == '-', ch = gc();
  while ('0' <= ch && ch <= '9')
    x = x * 10 + ch - 48, ch = gc();
  f && (x = -x);
}
inline void Read(char *str) {
  char ch = gc();
  while (ch < 32 || ch > 126)
    ch = gc();
  while (32 <= ch && ch <= 126)
    *(str++) = ch, ch = gc();
}
}; // namespace FastRead
using FastRead::Read;
using namespace std;
typedef long long LL;
const int N = 2e5 + 5;
const LL INF = -0x3f3f3f3f3f3f3f3f;
int n, m, q;
int la[N], ne[N], en[N], idx;
int fa[N], dep[N], siz[N], son[N], top[N], bot[N], id[N], rnk[N], dfst;
LL b[N], g[N], h[N];
LL sg[N], sh[N], sgb[N], shb[N];
struct Matrix {
  LL a00, a11, a20, a21, a22;
};
inline void Mul(Matrix &a, Matrix &b, Matrix &c) {
  c.a00 = a.a00 + b.a00;
  c.a11 = a.a11 + b.a11;
  c.a20 = max(a.a20 + b.a00, a.a22 + b.a20);
  c.a21 = max(a.a21 + b.a11, a.a22 + b.a21);
  c.a22 = a.a22 + b.a22;
}
inline void Mul(Matrix &a, LL c[]) {
  c[0] = a.a00;
  c[1] = a.a11;
  c[2] = max({a.a20, a.a21, a.a22});
}
inline void Init(Matrix &a, int u) {
  a.a00 = sg[u] + g[u];
  a.a11 = sh[u] + h[u] + b[u];
  a.a20 = sgb[u];
  a.a21 = a.a22 = max(sgb[u], shb[u] + b[u]);
}
inline LL Query(Matrix &a) { return max({a.a00, a.a11, a.a20, a.a21, a.a22}); }
struct Node {
  int ls, rs, fa;
  Matrix a;
} t[N * 4];
int rt[N], pos[N], pid;
inline void Insert(int u, int v) {
  static LL f[3];
  Mul(t[rt[v]].a, f);
  sg[u] += f[0], sh[u] += f[1], sgb[u] += max({f[0], f[1], f[2]}),
      shb[u] += max(f[1], f[2]);
}
inline void Delete(int u, int v) {
  static LL f[3];
  Mul(t[rt[v]].a, f);
  sg[u] -= f[0], sh[u] -= f[1], sgb[u] -= max({f[0], f[1], f[2]}),
      shb[u] -= max(f[1], f[2]);
}
inline void PushUp(int u) { Mul(t[t[u].ls].a, t[t[u].rs].a, t[u].a); }
inline void Build(int &u, int a, int b) {
  u = ++pid;
  if (a == b) {
    pos[a] = u, Init(t[u].a, rnk[a]);
    return;
  }
  int mid = (a + b) >> 1;
  Build(t[u].ls, a, mid);
  Build(t[u].rs, mid + 1, b);
  t[t[u].ls].fa = t[t[u].rs].fa = u;
  PushUp(u);
}
inline void Change(int i) {
  int u = pos[id[i]];
  Init(t[u].a, i);
  for (u = t[u].fa; u; u = t[u].fa)
    PushUp(u);
}
inline void Add(int a, int b) {
  ne[++idx] = la[a];
  la[a] = idx;
  en[idx] = b;
}
inline void DFS1(int u, int f) {
  fa[u] = f, dep[u] = dep[f] + 1, siz[u] = 1;
  for (int i = la[u]; i; i = ne[i]) {
    int v = en[i];
    if (v != f) {
      DFS1(v, u);
      siz[u] += siz[v];
      if (siz[v] > siz[son[u]])
        son[u] = v;
    }
  }
}
inline void DFS2(int u, int f) {
  top[u] = f, rnk[id[u] = ++dfst] = u;
  if (son[u]) {
    DFS2(son[u], f), bot[u] = bot[son[u]];
    for (int i = la[u]; i; i = ne[i]) {
      int v = en[i];
      if (v != fa[u] && v != son[u]) {
        DFS2(v, v);
        Insert(u, v);
      }
    }
  } else
    bot[u] = u;
  if (u == f)
    Build(rt[u], id[u], id[bot[u]]), t[rt[u]].fa = 0;
}
inline void Modify(int u) {
  int v = top[u], w = fa[v];
  while (w) {
    Delete(w, v);
    Change(u);
    Insert(w, v);
    u = w, v = top[u], w = fa[v];
  }
  Change(u);
}
inline void Solve() {
  Read(n), Read(m);
  for (int i = 1; i <= n; i++)
    la[i] = h[i] = g[i] = sg[i] = sh[i] = sgb[i] = shb[i] = son[i] = 0;
  idx = dfst = pid = 0;
  for (int i = 2; i <= n; i++) {
    int p;
    Read(p);
    Add(p, i);
  }
  for (int i = 1; i <= n; i++)
    Read(b[i]);
  DFS1(1, 0), DFS2(1, 1);
  LL sumg = 0;
  for (int i = 1; i <= m; i++) {
    int opt, u, d;
    Read(opt), Read(u), Read(d);
    if (opt == 1)
      g[u] += d, sumg += d;
    else
      h[u] += d;
    Modify(u);
    puts(Query(t[rt[1]].a) == sumg ? "YES" : "NO");
  }
}
int main() {
  int T;
  Read(T);
  while (T--)
    Solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/