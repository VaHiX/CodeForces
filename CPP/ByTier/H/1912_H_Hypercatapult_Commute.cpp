// Problem: CF 1912 H - Hypercatapult Commute
// https://codeforces.com/contest/1912/problem/H

/*
 * Problem: H. Hypercatapult Commute
 * 
 * Purpose: This code determines the minimum number of catapult launches needed to transport all passengers
 *          from their starting cities to destination cities in Byteland, using a graph-based approach.
 * 
 * Algorithm: 
 * - The problem is modeled as a directed graph where each edge represents a possible catapult travel.
 * - The solution attempts to break the graph into strongly connected components (SCCs) and then 
 *   find an Eulerian path for each component.
 * - It uses topological sorting and DFS to detect valid paths through nodes.
 * 
 * Time Complexity: O(n * (n + m)) in worst case due to checking each node for cycle detection and
 *                  traversals in the SCC.
 * Space Complexity: O(n + m) for storing the graph structure and auxiliary arrays.
 * 
 * Techniques:
 * - Union-Find (Disjoint Set Union) for finding connected components
 * - Depth-First Search (DFS) for finding connected components
 * - Topological sorting to process nodes in order
 * - Graph traversal for finding valid catapult paths
 */

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;
vector<vector<int>> g, b;
int n, m, v[1005], in[1005], rem[1005], ed[1005];
void dfs(int x, vector<int> &t) {
  v[x] = 1;
  t.push_back(x);
  for (int i : g[x])
    if (!v[i])
      dfs(i, t);
}
vector<pair<int, int>> ans;
void topo(queue<int> &q, queue<int> &order) {
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i : g[u]) {
      if ((--rem[i]) == ed[i]) {
        q.push(i);
        order.push(i);
      }
    }
  }
}
bool check(vector<int> &t) {
  for (int i : t)
    for (int j : g[i])
      in[j]++;
  for (int x = -1; x < (int)t.size(); x++) {
    int i = x >= 0 ? t[x] : 0;
    ed[i] = t.size();
    queue<int> q, order;
    for (int j : t) {
      rem[j] = in[j];
      if (rem[j] <= ed[j]) {
        q.push(j);
        order.push(j);
      }
    }
    topo(q, order);
    if (order.size() == t.size()) {
      if (i)
        order.push(i);
      int la = order.front();
      order.pop();
      while (!order.empty()) {
        int u = order.front();
        order.pop();
        ans.push_back({la, u});
        la = u;
      }
      return 1;
    }
    ed[i] = 0;
  }
  return 0;
}
int fa[1005], mp[1005][1005];
int fnd(int x) { return fa[x] == x ? x : fa[x] = fnd(fa[x]); }
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> m;
  g.resize(n + 1);
  b.resize(n + 1);
  for (int i = 1; i <= n; i++)
    fa[i] = i;
  for (int i = 1, u, v; i <= m; i++) {
    cin >> u >> v;
    if (!mp[u][v])
      g[u].push_back(v);
    mp[u][v] = 1;
    fa[fnd(v)] = fnd(u);
  }
  int res = 0;
  for (int i = 1; i <= n; i++)
    b[fnd(i)].push_back(i);
  for (int i = 1; i <= n; i++)
    if (fnd(i) == i) {
      if (!check(b[i]))
        return printf("-1"), 0;
    }
  printf("%d\n", ans.size());
  for (auto [a, b] : ans)
    printf("%d %d\n", a, b);
  return 0;
}


// https://github.com/VaHiX/CodeForces/