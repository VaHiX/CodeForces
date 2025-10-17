// Problem: CF 2041 K - Trophic Balance Species
// https://codeforces.com/contest/2041/problem/K

/*
 * Problem: K. Trophic Balance Species
 * Purpose: Find all trophic balance species in a directed graph representing an ecosystem.
 *          A trophic balance species is one where the absolute difference between number of 
 *          prey (reachable nodes) and predators (nodes that can reach it) is minimized.
 * Algorithms:
 *   - Tarjan's algorithm for finding Strongly Connected Components (SCCs)
 *   - Dynamic Programming on DAG derived from SCCs
 *   - BFS traversal to compute affected/reached node counts per component
 * 
 * Time Complexity: O(N + M), where N = nodes, M = edges
 * Space Complexity: O(N + M)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;
const int N = 2e5 + 10, M = 4 * N;
int n, m, degin[N], degout[N], res = 1e9;
unordered_map<int, bool> mp[N];
vector<int> ans;
int h[N], h1[N], ne[M], e[M], idx;
void add(int h[], int a, int b) { e[++idx] = b, ne[idx] = h[a], h[a] = idx; }
int dfn[N], low[N], viti;
int scc_cnt, be[N], cnt[N];
int q[N], tt;
bool in[N];
void tarjan(int x) {
  // DFS to find Strongly Connected Components using Tarjan's algorithm
  dfn[x] = low[x] = ++viti, in[q[++tt] = x] = 1;
  for (int i = h[x]; i; i = ne[i]) {
    int j = e[i];
    if (!dfn[j])
      tarjan(j), low[x] = min(low[x], low[j]);
    else if (in[j])
      low[x] = min(low[x], dfn[j]);
  }
  if (dfn[x] == low[x]) {
    int t = -1;
    scc_cnt++;
    while (t != x)
      in[t = q[tt--]] = 0, cnt[be[t] = scc_cnt]++;
  }
}
bool flag[N];
int f[N], suf[N];
int dp(int x) {
  // Dynamic programming to find max reachable score for each SCC
  if (~f[x])
    return f[x];
  f[x] = 0;
  for (int i = h[x]; i; i = ne[i])
    if (dp(e[i]) > f[x])
      f[x] = dp(e[i]), suf[x] = e[i];
  return f[x] += flag[x];
}
int sum;
void bfs(int x) {
  // BFS to compute the total size of a component
  in[q[++tt] = x] = 1, sum += cnt[x];
  while (tt) {
    int t = q[tt--];
    for (int i = h[t]; i; i = ne[i])
      if (!in[e[i]])
        in[q[++tt] = e[i]] = 1, sum += cnt[e[i]];
  }
}
void solve(int deg[]) {
  // Iterate greedily to minimize degree difference
  memset(flag, 1, sizeof(flag));
  memset(suf, 0, sizeof(suf));
  while (1) {
    memset(f, -1, sizeof(f));
    int maxn = 0, id = 0;
    for (int i = 1; i <= scc_cnt; i++)
      if (flag[i] && dp(i) > maxn)
        maxn = dp(i), id = i;
    if (!maxn)
      return;
    vector<int> s(1, id);
    while (f[suf[s.back()]] > 0)
      s.push_back(suf[s.back()]);
    memset(in, 0, sizeof(in)), sum = 0;
    for (int i = s.size() - 1; ~i; i--)
      bfs(s[i]), deg[s[i]] = sum, flag[s[i]] = 0;
  }
}
int main() {
  cin >> n >> m;
  for (int i = 1, a, b; i <= m; i++)
    scanf("%d%d", &a, &b), add(h, a, b);
  for (int i = 1; i <= n; i++)
    if (!dfn[i])
      tarjan(i);
  for (int i = 1; i <= n; i++)
    for (int j = h[i]; j; j = ne[j])
      if (be[i] != be[e[j]] && !mp[be[i]][be[e[j]]])
        add(h1, be[i], be[e[j]]), mp[be[i]][be[e[j]]] = 1;
  memset(h, 0, sizeof(h)), idx = 0;
  for (int i = 1; i <= scc_cnt; i++)
    for (int j = h1[i]; j; j = ne[j])
      add(h, i, e[j]);
  solve(degin);
  memset(h, 0, sizeof(h)), idx = 0;
  for (int i = 1; i <= scc_cnt; i++)
    for (int j = h1[i]; j; j = ne[j])
      add(h, e[j], i);
  solve(degout);
  for (int i = 1; i <= n; i++)
    if (abs(degin[be[i]] - degout[be[i]]) < res)
      res = abs(degin[be[i]] - degout[be[i]]), ans.clear(), ans.push_back(i);
    else if (abs(degin[be[i]] - degout[be[i]]) == res)
      ans.push_back(i);
  for (int i : ans)
    printf("%d ", i);
  return 0;
}


// https://github.com/VaHiX/codeForces/