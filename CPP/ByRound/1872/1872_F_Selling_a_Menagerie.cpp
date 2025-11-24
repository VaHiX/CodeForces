// Problem: CF 1872 F - Selling a Menagerie
// https://codeforces.com/contest/1872/problem/F

/*
Purpose: This code solves the problem of selling animals from a menagerie in an order that maximizes profit.
         Each animal is afraid of another, and the profit depends on whether the afraid animal has been sold before.
         The approach uses topological sorting for trees and cycle detection for circular dependencies.

Algorithms/Techniques:
- Topological sort to process nodes with in-degree 0
- Cycle detection and handling in directed graphs
- Greedy selection within cycles to minimize cost impact

Time Complexity: O(n) - Linear time processing for each node and edge
Space Complexity: O(n) - Storage for graph, in-degrees, visited array, and result
*/
#include <algorithm>
#include <iostream>
#include <vector>

#define _PRINT_ 1
#define _TEST_ 1
#define _SOLVE_ 1
#if defined(DEBUG) && _PRINT_ == 1
#include "debug.h"
#else
#define print(x, ...) 0
#define debug(x, ...) 0
#define verify(x, ...) 0
#endif
using namespace std;
using ll = long long;
constexpr int inf = 1e9 + 1;
constexpr ll llinf = 1e18 + 1;
void solve() {
  int n;
  cin >> n;
  vector<int> g(n);
  for (int u = 0; u < n; u++) {
    int v;
    cin >> v;
    --v;
    g[u] = v;
  }
  vector<int> cost(n);
  for (int i = 0; i < n; i++) {
    cin >> cost[i];
  }
  vector<int> ans;
  vector<int> ideg(n);
  for (int u = 0; u < n; u++) {
    int v = g[u];
    ideg[v]++;
  }
  vector<bool> vis(n);
  vector<int> que;
  for (int u = 0; u < n; u++) {
    if (ideg[u] == 0) {
      que.push_back(u);
    }
  }
  while (!que.empty()) {
    int u = que.back();
    que.pop_back();
    vis[u] = true;
    ans.push_back(u);
    int v = g[u];
    if (--ideg[v] == 0) {
      que.push_back(v);
    }
  }
  for (int u = 0; u < n; u++) {
    if (!vis[u]) {
      int mn = inf, x;
      int v = u;
      while (true) {
        vis[v] = true;
        if (cost[v] < mn) {
          mn = cost[v];
          x = v;
        }
        v = g[v];
        if (v == u) {
          break;
        }
      }
      int nx = g[x];
      v = nx;
      while (true) {
        ans.push_back(v);
        v = g[v];
        if (v == nx) {
          break;
        }
      }
    }
  }
  for (int i = 0; i < n; i++) {
    cout << ans[i] + 1 << " \n"[i == n - 1];
  }
}
int main() {
#ifdef DEBUG
  freopen("input.txt", "r", stdin);
#endif
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/