/*
 * Problem URL : https://codeforces.com/problemset/problem/2115/F1
 * Submit Date : 2025-08-16
 */

#include <algorithm>
#include <cstdio>
#include <utility>
#define il inline
#define vo void
using namespace std;
const int N = 3e5, S = N << 6;
struct Que {
  static int val[S << 1], nxt[S << 1], tot;
  int h, t;
  il vo push(int x) {
    if (!h)
      h = t = ++tot, val[h] = x;
    else
      t = nxt[t] = ++tot, val[t] = x;
  }
  il vo pop() {
    if (h == t)
      h = t = 0;
    else
      h = nxt[h];
  }
  Que() : h(0), t(0) {}
};
int Que::val[S << 1], Que::nxt[S << 1], Que::tot;
int n, q;
int rt, tot, sz[S], ch[S][2], t[S];
Que f[S];
bool bz[N + 2];
il int newx() {
  int u = ++tot;
  sz[u] = ch[u][0] = ch[u][1] = t[u] = 0;
  return u;
}
il int newl() {
  int u = newx();
  sz[u] = 1;
  return u;
}
il vo pushup(int u) { sz[u] = sz[ch[u][0]] + sz[ch[u][1]]; }
il int join(int u, int v) {
  int x = newx();
  ch[x][0] = u, ch[x][1] = v;
  pushup(x);
  f[u].push(x);
  f[v].push(x);
  return x;
}
il vo pudown(int u) {
  if (sz[u] != 1 && t[u]) {
    swap(ch[u][0], ch[u][1]);
    t[ch[u][0]] ^= 1;
    t[ch[u][1]] ^= 1;
    t[u] = 0;
  }
}
il pair<int, int> cut(int u) {
  pudown(u);
  return {ch[u][0], ch[u][1]};
}
il bool hev(int x, int y) { return x > 3 * y; }
int merge(int u, int v) {
  if (!u || !v)
    return u | v;
  if (hev(sz[u], sz[v])) {
    auto [x, y] = cut(u);
    if (hev(sz[y] + sz[v], sz[x])) {
      auto [a, b] = cut(y);
      return merge(merge(x, a), merge(b, v));
    } else
      return merge(x, merge(y, v));
  } else if (hev(sz[v], sz[u])) {
    auto [x, y] = cut(v);
    if (hev(sz[u] + sz[x], sz[y])) {
      auto [a, b] = cut(x);
      return merge(merge(u, a), merge(b, y));
    } else
      return merge(merge(u, x), y);
  }
  return join(u, v);
}
pair<int, int> spl(int u, int k) {
  if (!k || !u)
    return {0, u};
  if (k == sz[u])
    return {u, 0};
  auto [x, y] = cut(u);
  if (sz[x] < k) {
    auto [a, b] = spl(y, k - sz[x]);
    return {merge(x, a), b};
  } else {
    auto [a, b] = spl(x, k);
    return {a, merge(b, y)};
  }
}
int build(int l, int r) {
  if (l == r)
    return newl();
  int mid = l + r >> 1;
  return join(build(l, mid), build(mid + 1, r));
}
void rever(int r) {
  auto [x, y] = spl(rt, r);
  t[x] ^= 1;
  rt = merge(x, y);
}
void ins(int r, int k) {
  auto [x, y] = spl(rt, r);
  f[x].push(-k);
  rt = merge(x, y);
}
int loc(int u, int k) {
  if (sz[u] == 1)
    return u;
  pudown(u);
  return sz[ch[u][0]] < k ? loc(ch[u][1], k - sz[ch[u][0]]) : loc(ch[u][0], k);
}
int ask(int u) {
  if (u < 0)
    return bz[-u] ? 0 : -u;
  int p = 0;
  for (int i = f[u].h; i;) {
    int x = f[u].val[i];
    int t = ask(x);
    if (t > 0)
      return t;
    if (t == -1)
      p = i, i = f[u].nxt[i];
    else {
      if (!p)
        i = f[u].nxt[i], f[u].pop();
      else
        i = f[u].nxt[p] = f[u].nxt[i];
    }
  }
  return p || u == rt ? -1 : 0;
}
int main() {
  scanf("%d%d", &n, &q);
  rt = build(1, n);
  for (int i = 1, lst = 0; i <= q; ++i) {
    int op, x, y;
    scanf("%d%d%d", &op, &x, &y);
    if (op == 1) {
      x = (x + lst - 1) % n + 1;
      ins(x, i);
    } else if (op == 2) {
      x = (x + lst - 1) % n + 1;
      rever(x);
    } else {
      x = (x + lst - 1) % q + 1;
      if (x < i)
        bz[x] = 1;
    }
    lst = max(0, ask(loc(rt, (y + lst - 1) % n + 1)));
    printf("%d\n", lst);
  }
  return 0;
}