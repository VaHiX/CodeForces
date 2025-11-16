// Problem: CF 1957 F1 - Frequency Mismatch (Easy Version)
// https://codeforces.com/contest/1957/problem/F1

/*
 * Problem: F1. Frequency Mismatch (Easy Version)
 * Purpose: Given an undirected tree with node values, answer queries about the difference in frequency of values on two paths.
 * Algorithm: 
 *   - Use a Persistent Segment Tree to store the frequency of values in the path from root to each node.
 *   - Use Binary Lifting for LCA computation.
 *   - For each query, compute the frequency difference between paths using persistent segment trees and binary search on values.
 *
 * Time Complexity:
 *   - Preprocessing: O(n log n) for DFS + LCA construction
 *   - Each query: O(log V) where V = 1e5 (value range)
 *   - Total: O(n log n + q * log V)
 *
 * Space Complexity:
 *   - O(n * log V) for persistent segment trees
 */

#include <stdio.h>
#include <time.h>
#include <algorithm>
#include <random>
#include <vector>

#define mid (l + r >> 1)
using namespace std;
const int maxn = 100005, maxt = maxn * 30, V = 1e5, maxk = 20;
int n, m, anss, dfns, tot;
int a[maxn], rt[maxn], lc[maxt], rc[maxt], ans[maxn], dfn[maxn], st[maxk][maxn],
    dep[maxn], lg[maxn], fa[maxn];
unsigned long long sum[maxt], rd[maxn];
vector<int> v[maxn];
mt19937_64 rnd(time(0));

// Modify persistent segment tree to insert value v at position p
void modify(int l, int r, int &now, int p, unsigned long long v) {
  tot++, lc[tot] = lc[now], rc[tot] = rc[now], sum[tot] = sum[now], now = tot;
  sum[now] += v;
  if (l == r)
    return;
  if (p <= mid)
    modify(l, mid, lc[now], p, v);
  else
    modify(mid + 1, r, rc[now], p, v);
}

// Query the sum of values in range [L, R] in the persistent segment tree
unsigned long long query(int l, int r, int now, int L, int R) {
  if (L <= l && r <= R)
    return sum[now];
  unsigned long long res = 0;
  if (L <= mid)
    res += query(l, mid, lc[now], L, R);
  if (mid < R)
    res += query(mid + 1, r, rc[now], L, R);
  return res;
}

// DFS to build persistent segment trees and compute LCA
void dfs(int x, int last) {
  dfn[x] = ++dfns, st[0][dfns] = last, dep[x] = dep[last] + 1, fa[x] = last;
  modify(1, V, rt[x], a[x], rd[a[x]]); // Add current node's value to segment tree
  for (int i = 0; i < v[x].size(); i++) {
    int y = v[x][i];
    if (y == last)
      continue;
    rt[y] = rt[x], dfs(y, x);
  }
}

// Calculate minimum by depth
int calc(int a, int b) { return dep[a] < dep[b] ? a : b; }

// Compute LCA using binary lifting
int lca(int x, int y) {
  if (x == y)
    return x;
  int l = min(dfn[x], dfn[y]) + 1, r = max(dfn[x], dfn[y]), k = lg[r - l + 1];
  return calc(st[k][l], st[k][r - (1 << k) + 1]);
}

// Get count of values in range [L, R] along path from u to v
unsigned long long C(int u, int v, int w, int L, int R) {
  return query(1, V, rt[u], L, R) + query(1, V, rt[v], L, R) -
         2 * query(1, V, rt[w], L, R) + (L <= a[w] && a[w] <= R ? rd[a[w]] : 0);
}

// Find values that differ in frequency on two paths
void find(int l, int r, int u1, int v1, int w1, int z1, int u2, int v2, int w2,
          int z2, int k) {
  // Early termination if no differences or result already full
  if (sum[u1] + sum[v1] - sum[w1] - sum[z1] ==
          sum[u2] + sum[v2] - sum[w2] - sum[z2] ||
      anss >= k)
    return;
  if (l == r) {
    ans[++anss] = l;
    return;
  }
  if (anss >= k)
    return;
  find(l, mid, lc[u1], lc[v1], lc[w1], lc[z1], lc[u2], lc[v2], lc[w2], lc[z2],
       k);
  if (anss >= k)
    return;
  find(mid + 1, r, rc[u1], rc[v1], rc[w1], rc[z1], rc[u2], rc[v2], rc[w2],
       rc[z2], k);
}

int main() {
  scanf("%d", &n), lg[0] = -1;
  for (int i = 1; i <= n; i++)
    lg[i] = lg[i >> 1] + 1;
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  for (int i = 1; i <= V; i++)
    rd[i] = rnd();
  for (int i = 1, x, y; i < n; i++)
    scanf("%d%d", &x, &y), v[x].emplace_back(y), v[y].emplace_back(x);
  dfs(1, 0);
  for (int i = 1; i <= 18; i++)
    for (int j = 1; j + (1 << i) - 1 <= n; j++)
      st[i][j] = calc(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
  scanf("%d", &m);
  for (int T = 1, u1, v1, u2, v2, k; T <= m; T++) {
    scanf("%d%d%d%d%d", &u1, &v1, &u2, &v2, &k);
    int w1 = lca(u1, v1), w2 = lca(u2, v2);
    anss = 0;
    find(1, V, rt[u1], rt[v1], rt[w1], rt[fa[w1]], rt[u2], rt[v2], rt[w2],
         rt[fa[w2]], k);
    printf("%d ", anss);
    for (int i = 1; i <= anss; i++)
      printf("%d ", ans[i]);
    puts("");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/