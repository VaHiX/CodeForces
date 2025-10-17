// Problem: CF 2152 G - Query Jungle
// https://codeforces.com/contest/2152/problem/G

/*
 * Problem: G. Query Jungle
 *
 * Purpose:
 * This code solves a tree query problem where we need to find the minimum number of paths from root (vertex 1)
 * that cover all vertices with monsters. It supports cumulative queries where we invert the status of monsters in
 * a subtree. The solution uses a DFS Euler tour with a segment tree to efficiently maintain the answer after each query.
 *
 * Techniques:
 * - Euler Tour of Tree
 * - Segment Tree with Lazy Propagation
 * - Binary Indexed Tree-like approach on segment tree for path count calculation
 *
 * Time Complexity:
 * - Preprocessing: O(n)
 * - Each Query: O(log n)
 * - Overall: O(n + q * log n) per test case
 *
 * Space Complexity:
 * - O(n) for storing tree and segment tree
 */

#include <stdio.h>
#include <iostream>
#include <utility>

using namespace std;
#define ll int
#define i8 __int128
void write1(ll x) {
  if (x < 0)
    putchar('-'), x = -x;
  if (x > 9)
    write1(x / 10);
  putchar(x % 10 + '0');
}
void write(ll x) {
  static ll sta[35];
  ll top = 0;
  do {
    sta[top++] = x % 10, x /= 10;
  } while (x);
  while (top)
    putchar(sta[--top] + 48);
}
ll read() {
  ll x = 0, w = 1;
  char ch = 0;
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      w = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + (ch - '0');
    ch = getchar();
  }
  return x * w;
}
const ll N = 3e5 + 10;
ll to[N << 1], nxt[N << 1], bh[N], tot = 1, n, q, olx[N << 1], mxdfn[N], dfn[N],
                                   tim = 0;
bool ys[N];
void add(ll u, ll v) {
  to[++tot] = v;
  nxt[tot] = bh[u];
  bh[u] = tot;
}
void dfs1(ll u, ll fath) {
  dfn[u] = ++tim;
  mxdfn[u] = tim;
  if (!ys[u])
    olx[tim] = 0;
  else
    olx[tim] = 2;
  for (ll i = bh[u]; i; i = nxt[i]) {
    ll v = to[i];
    if (v == fath)
      continue;
    dfs1(v, u);
  }
  if (!ys[u])
    olx[++tim] = 1;
  else
    olx[++tim] = 3;
  mxdfn[u] = tim;
}
struct mqmh {
  ll head[2];
  void csh() { head[0] = head[1] = 0; }
};
mqmh merge(mqmh ls, mqmh rs) {
  mqmh x;
  x.csh();
  x.head[0] = ls.head[0] + rs.head[ls.head[0] & 1];
  x.head[1] = ls.head[1] + rs.head[(ls.head[1] & 1) ^ 1];
  return x;
}
struct mqm {
  mqmh nm[2];
  void csh() {
    nm[0].csh();
    nm[1].csh();
  }
};
mqm merge(mqm ls, mqm rs) {
  mqm x;
  x.csh();
  x.nm[0] = merge(ls.nm[0], rs.nm[0]);
  x.nm[1] = merge(ls.nm[1], rs.nm[1]);
  return x;
}
struct segatree {
  mqm tr[N << 4];
  bool lt[N << 4];
#define ls(u) (u << 1)
#define rs(u) (u << 1 | 1)
  void pushup(ll u) { tr[u] = merge(tr[ls(u)], tr[rs(u)]); }
  void hard(ll u) {
    swap(tr[u].nm[0], tr[u].nm[1]);
    lt[u] ^= 1;
  }
  void build(ll u, ll l, ll r) {
    tr[u].csh();
    lt[u] = 0;
    if (l == r) {
      if (olx[l] <= 1)
        tr[u].nm[0].head[olx[l]] = 1;
      else
        tr[u].nm[1].head[olx[l] - 2] = 1;
      return;
    }
    ll mid = (l + r) >> 1;
    build(ls(u), l, mid);
    build(rs(u), mid + 1, r);
    pushup(u);
  }
  void pushdown(ll u) {
    if (!lt[u])
      return;
    hard(ls(u));
    hard(rs(u));
    lt[u] = 0;
  }
  void mdf(ll u, ll l, ll r, ll ql, ll qr) {
    if (ql <= l && r <= qr) {
      hard(u);
      return;
    }
    ll mid = (l + r) >> 1;
    pushdown(u);
    if (ql <= mid)
      mdf(ls(u), l, mid, ql, qr);
    if (mid < qr)
      mdf(rs(u), mid + 1, r, ql, qr);
    pushup(u);
  }
  mqm find(ll u, ll l, ll r, ll ql, ll qr) {
    if (ql <= l && r <= qr)
      return tr[u];
    ll mid = (l + r) >> 1;
    pushdown(u);
    if (qr <= mid)
      return find(ls(u), l, mid, ql, qr);
    else if (mid < ql)
      return find(rs(u), mid + 1, r, ql, qr);
    return merge(find(ls(u), l, mid, ql, qr), find(rs(u), mid + 1, r, ql, qr));
  }
} jb;
ll as[N];
void work() {
  for (ll i = 1; i <= n; i++)
    bh[i] = 0;
  tim = 0;
  tot = 1;
  n = read();
  for (ll i = 1; i <= n; i++)
    ys[i] = read();
  for (ll i = 1; i < n; i++) {
    ll u = read(), v = read();
    add(u, v);
    add(v, u);
  }
  dfs1(1, 1);
  jb.build(1, 1, n << 1);
  as[0] = jb.tr[1].nm[1].head[0] / 2;
  q = read();
  for (ll i = 1; i <= q; i++) {
    ll u = read();
    jb.mdf(1, 1, n << 1, dfn[u], mxdfn[u]);
    as[i] = jb.tr[1].nm[1].head[0] / 2;
  }
  for (ll i = 0; i <= q; i++)
    cout << as[i] << '\n';
}
int main() {
  ll t = read();
  while (t--)
    work();
}


// https://github.com/VaHiX/CodeForces/