// Problem: CF 1870 H - Standard Graph Problem
// https://codeforces.com/contest/1870/problem/H

/*
 * Problem: H. Standard Graph Problem
 * 
 * Algorithm: 
 * - This code uses a combination of:
 *   1. Link-Cut Tree (LCT) with lazy propagation for dynamic connectivity
 *   2. Tarjan's algorithm for finding strongly connected components (SCCs)
 *   3. Heavy-light decomposition with binary lifting for tree queries
 *   4. Set-based structure for maintaining highlighted vertices
 * 
 * Time Complexity: O((n + m + q) * log(n))
 * Space Complexity: O(n + m + q)
 * 
 * Purpose:
 *   Given a directed weighted graph with vertices that can be highlighted or normal,
 *   compute the minimum cost to ensure every normal vertex reaches at least one 
 *   highlighted vertex. Each query toggles the state of a vertex and updates the cost.
 */
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;
const int maxn = 400005, maxk = 20;
int n, m, q, tot, stp, top, flg, cnt, dfns;
int rt[maxn], dsu[maxn], vis[maxn], lc[maxn], rc[maxn], lazy[maxn], dis[maxn],
    stk[maxn], dfn[maxn], id[maxn], lg[maxn], st[maxk][maxn], dep[maxn];
long long ans;
long long val[maxn], sum[maxn];
vector<int> v[maxn];
set<int> s;
string str;
int find(int x) { return dsu[x] == x ? x : dsu[x] = find(dsu[x]); }
struct edge {
  int x, y, z;
} e[maxn];
int newnode(int x, int y, int z) {
  cnt++, e[cnt] = edge{x, y, z}, dis[cnt] = 1;
  return cnt;
}
void pushup(int now) {
  if (dis[lc[now]] < dis[rc[now]])
    swap(lc[now], rc[now]);
  dis[now] = dis[rc[now]] + 1;
}
void getlazy(int now, int v) {
  lazy[now] += v, e[now] = edge{e[now].x, e[now].y, e[now].z + v};
}
void pushdown(int now) {
  if (lazy[now])
    getlazy(lc[now], lazy[now]), getlazy(rc[now], lazy[now]), lazy[now] = 0;
}
int merge(int a, int b) {
  if (a == 0 || b == 0)
    return a | b;
  pushdown(a), pushdown(b);
  if (e[a].z > e[b].z || (e[a].z == e[b].z && a > b))
    swap(a, b);
  rc[a] = merge(rc[a], b), pushup(a);
  return a;
}
int pop(int a) {
  pushdown(a);
  return merge(lc[a], rc[a]);
}
void tarjan(int x) {
  if (vis[x] && vis[x] != stp)
    return;
  if (vis[x] == stp) {
    tot++, dsu[tot] = tot;
    int y = -1;
    while (y != x)
      y = stk[top], dsu[y] = tot, v[tot].emplace_back(y),
      rt[tot] = merge(rt[tot], rt[y]), top--;
    tarjan(tot);
    return;
  }
  vis[x] = stp, stk[++top] = x;
  while (rt[x] && find(e[rt[x]].y) == x)
    rt[x] = pop(rt[x]);
  if (rt[x] == 0) {
    val[x] = 1e12, v[0].emplace_back(x);
    return;
  }
  edge cur = e[rt[x]];
  val[x] = cur.z, rt[x] = pop(rt[x]), getlazy(rt[x], -cur.z),
  tarjan(find(cur.y));
  if (find(x) == x)
    v[0].emplace_back(x);
}
void dfs(int x, int last) {
  dfn[x] = ++dfns, id[dfns] = x, st[0][dfns] = last, dep[x] = dep[last] + 1,
  sum[x] = sum[last] + val[x], ans += val[x];
  for (int i = 0; i < v[x].size(); i++)
    dfs(v[x][i], x);
}
int calc(int a, int b) { return dep[a] < dep[b] ? a : b; }
int lca(int x, int y) {
  if (x == y)
    return x;
  int l = min(dfn[x], dfn[y]) + 1, r = max(dfn[x], dfn[y]), k = lg[r - l + 1];
  return calc(st[k][l], st[k][r - (1 << k) + 1]);
}
int main() {
  ios::sync_with_stdio(false);
  cin >> n >> m >> q, tot = n, lg[0] = -1;
  for (int i = 1; i <= n; i++)
    dsu[i] = i;
  for (int i = 1, x, y, z; i <= m; i++)
    cin >> x >> y >> z, rt[x] = merge(rt[x], newnode(x, y, z));
  for (int i = 1; i <= n; i++)
    if (vis[i] == 0)
      top = 0, stp++, tarjan(i);
  for (int i = 0; i < v[0].size(); i++)
    dfs(v[0][i], 0);
  for (int i = 1; i <= tot; i++)
    lg[i] = lg[i >> 1] + 1;
  for (int i = 1; i <= 19; i++)
    for (int j = 1; j + (1 << i) - 1 <= tot; j++)
      st[i][j] = calc(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
  while (q--) {
    int x;
    cin >> str >> x;
    if (str == "+") {
      set<int>::iterator it = s.lower_bound(dfn[x]);
      ans -= sum[x];
      int suc = -1, pre = -1;
      if (it != s.end())
        suc = id[*it], ans += sum[lca(x, id[*it])];
      if (it != s.begin())
        it--, pre = id[*it], ans += sum[lca(x, id[*it])];
      if (pre != -1 && suc != -1)
        ans -= sum[lca(pre, suc)];
      s.insert(dfn[x]);
    }
    if (str == "-") {
      s.erase(dfn[x]);
      set<int>::iterator it = s.lower_bound(dfn[x]);
      ans += sum[x];
      int suc = -1, pre = -1;
      if (it != s.end())
        suc = id[*it], ans -= sum[lca(x, id[*it])];
      if (it != s.begin())
        it--, pre = id[*it], ans -= sum[lca(x, id[*it])];
      if (pre != -1 && suc != -1)
        ans += sum[lca(pre, suc)];
    }
    if (ans >= 1e12)
      puts("-1");
    else
      printf("%lld\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/