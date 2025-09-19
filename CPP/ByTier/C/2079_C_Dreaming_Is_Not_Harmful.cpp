/*
 * Problem URL : https://codeforces.com/contest/2079/problem/C
 * Submit Date : 2025-08-25
 */

#include <bits/stdc++.h>
int N, Q, pa[500009], ta[500009], as[500009], v[500009], iv[500009], vi[500009],
    v2[500009], to[500009], nxt[500009], hd[500009], k, kk, t[500009],
    dfn[500009], top[500009], siz[500009], son[500009];
void l(int u, int v) {
  to[++k] = v;
  nxt[k] = hd[u];
  hd[u] = k;
}
void dfs(int n, int f) {
  siz[n] = 1;
  for (int i = hd[n]; i; i = nxt[i]) {
    dfs(to[i], n);
    siz[n] += siz[to[i]];
    if (siz[son[n]] < siz[to[i]])
      son[n] = to[i];
  }
}
void dfs2(int n, int tp) {
  top[n] = tp;
  dfn[n] = ++kk;
  if (son[n] == 0)
    return;
  dfs2(son[n], tp);
  for (int i = hd[n]; i; i = nxt[i]) {
    if (son[n] == to[i])
      continue;
    dfs2(to[i], to[i]);
  }
}
int sg[1200009], la[1200009];
#define ls (n << 1)
#define rs ((n << 1) | 1)
#define md ((l + r) >> 1)
int qr(int n, int l, int r, int L, int R) {
  if (L <= l && r <= R)
    return sg[n];
  int as = 0;
  if (md >= L)
    as = std::max(as, qr(ls, l, md, L, R));
  if (R > md)
    as = std::max(as, qr(rs, md + 1, r, L, R));
  return as + la[n];
}
void up(int n, int l, int r, int L, int R) {
  if (L <= l && r <= R) {
    la[n]++;
    sg[n]++;
    return;
  }
  if (md >= L)
    up(ls, l, md, L, R);
  if (R > md)
    up(rs, md + 1, r, L, R);
  sg[n] = std::max(sg[ls], sg[rs]) + la[n];
}
signed main(void) {
  scanf("%d %d", &N, &Q);
  for (int i = 2; i <= N; i++) {
    scanf("%d", &pa[i]);
    ta[i] = pa[i];
    l(pa[i], i);
  }
  for (int i = 1; i <= N; i++) {
    scanf("%d", &v[i]);
    iv[v[i]] = i;
  }
  std::set<int> ss;
  ss.insert(v[1]);
  int ll = 0;
  while (!ss.empty()) {
    int a = *ss.rbegin();
    ss.erase(a);
    a = iv[a];
    t[++ll] = a;
    for (int i = hd[a]; i; i = nxt[i])
      ss.insert(v[to[i]]);
  }
  kk = 0;
  dfs(1, 0);
  dfs2(1, 1);
  for (int i = 1; i <= N; i++) {
    int x = t[i], rr = N + 1, aa = 0;
    while (x) {
      if (rr - dfn[x] >= 2)
        aa = std::max(aa, qr(1, 1, N, dfn[x] + 1, rr - 1));
      up(1, 1, N, dfn[top[x]], dfn[x]);
      rr = dfn[top[x]];
      x = pa[top[x]];
    }
    if (rr >= 2)
      aa = std::max(aa, qr(1, 1, N, 1, rr - 1));
    as[t[i]] = i - aa - 1;
  }
  while (Q--) {
    int x;
    scanf("%d", &x);
    printf("%d ", as[x]);
  }
}