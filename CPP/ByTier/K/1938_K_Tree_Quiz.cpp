/*
 * Problem URL : https://codeforces.com/contest/1938/problem/K
 * Submit Date : 2025-09-07
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define mid ((l + r) >> 1)

struct Node {
  int l, r, s;
} pt[5005005];
int pc;

int n, m, sz[100100], child[100100], in[100100], out[100100], rev[100100], cnt,
    r[100100];
vector<int> v[100100];
vector<array<int, 2>> query[100100];
ll ans[100100];

int build_pst(int l = 1, int r = n) {
  int u = ++pc;
  if (l == r)
    return u;
  pt[u].l = build_pst(l, mid);
  pt[u].r = build_pst(mid + 1, r);
  return u;
}

int update_pst(int u, int id, int l = 1, int r = n) {
  if (id < l || r < id)
    return u;

  int x = ++pc;
  pt[x] = pt[u], pt[x].s++;
  if (l == r)
    return x;

  pt[x].l = update_pst(pt[x].l, id, l, mid);
  pt[x].r = update_pst(pt[x].r, id, mid + 1, r);
  return x;
}

int find_kth_pst(int L, int ml, int mr, int R, int k, int l = 1, int r = n) {
  if (l == r)
    return l;

  int C = pt[pt[R].l].s - pt[pt[L].l].s;
  int c = pt[pt[mr].l].s - pt[pt[ml].l].s;

  if (C - c >= k)
    return find_kth_pst(pt[L].l, pt[ml].l, pt[mr].l, pt[R].l, k, l, mid);
  return find_kth_pst(pt[L].r, pt[ml].r, pt[mr].r, pt[R].r, k - C + c, mid + 1,
                      r);
}

void dfs(int u, int p) {
  sz[u] = 1, in[u] = ++cnt, rev[in[u]] = u;
  for (auto x : v[u])
    dfs(x, u), sz[u] += sz[x];
  out[u] = cnt;
}

int t[100100];

void update(int b, int x) {
  while (b <= n)
    t[b] += x, b += b & -b;
}
array<int, 2> find_kth(int k) {
  int re1 = 0, re2 = 0;
  for (int i = 19; i >= 0; i--)
    if (re1 + (1 << i) <= n && re2 + t[re1 + (1 << i)] < k)
      re1 += 1 << i, re2 += t[re1];
  return {re1 + 1, re2};
}

int find_kth_subtree(int u, int k) {
  return find_kth_pst(r[in[u] - 1], r[max(0, in[child[u]] - 1)],
                      r[out[child[u]]], r[out[u]], k);
}

void dfs2(int u) {
  update(u, sz[u]);

  for (auto [k, id] : query[u]) {
    auto [L, M] = find_kth(k);

    int K = k - M;
    int y = find_kth_subtree(L, K);
    ans[id] = 1ll * (u - 1) * n * n + 1ll * (L - 1) * n + y - 1;
  }
  for (auto x : v[u]) {
    update(u, -sz[x]);
    child[u] = x;
    dfs2(x);
    update(u, sz[x]);
  }
  update(u, -sz[u]);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> m;
  int root = 0;
  for (int i = 1; i <= n; i++) {
    int p;
    cin >> p;
    if (p)
      v[p].push_back(i);
    else
      root = i;
  }
  dfs(root, 0);
  r[0] = build_pst();
  for (int i = 1; i <= n; i++)
    r[i] = update_pst(r[i - 1], rev[i]);

  for (int i = 1; i <= m; i++) {
    ll q;
    cin >> q;
    query[(q - 1) / n + 1].push_back({int((q - 1) % n + 1), i});
  }
  dfs2(root);
  for (int i = 1; i <= m; i++)
    cout << ans[i] << "\n";
}