// Problem: CF 2113 E - From Kazan with Love
// https://codeforces.com/contest/2113/problem/E

/*
E. From Kazan with Love
Algorithms:
- Tree traversal using DFS to build parent and depth information
- BFS-like simulation with time tracking to model enemy movement and Marat's possible paths
- Path tracking for each enemy from their home to work
- Dynamic update of conflict points using cnt (count) and can (availability) arrays

Time Complexity: O(n * m + n^2)
Space Complexity: O(n + m)

This is a complex simulation problem involving shortest path queries on a tree with dynamic constraints.
We simulate each moment in time where enemies move along their paths, and calculate optimal times for Marat to reach his destination while avoiding conflicts.
*/

#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <vector>

#pragma GCC optimize("O3")
using namespace std;
constexpr int MAXN = 1e5 + 1;
vector<int> g[MAXN];
int can[MAXN], cnt[MAXN]; // can[i]: whether vertex i is available for Marat,
                          // cnt[i]: number of enemies currently "watching" vertex i
int depth[MAXN], parent[MAXN]; // Depth and parent information for path computation

// Get path from u to v using parent pointers; includes both u and v
vector<int> get_path(int u, int v) {
  vector<int> a, b;
  while (u != v) {
    if (depth[u] > depth[v]) {
      a.push_back(u);
      u = parent[u];
    } else {
      b.push_back(v);
      v = parent[v];
    }
  }
  vector<int> res = a;
  res.push_back(u);
  res.insert(res.end(), b.rbegin(), b.rend());
  return res;
}

// DFS to compute depth and parent information for all nodes
void dfs(int u, int prev = -1) {
  for (int v : g[u]) {
    if (v == prev)
      continue;
    depth[v] = depth[u] + 1;
    parent[v] = u;
    dfs(v, u);
  }
}

void solve() {
  int n, m, x, y;
  cin >> n >> m >> x >> y;
  
  // Clear previous data
  for (int i = 1; i <= n; i++) {
    g[i].clear();
    can[i] = false;
    cnt[i] = 0;
  }
  
  // Read edges
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  
  dfs(1); // Build tree structure with root at 1

  vector<vector<int>> paths(m); // Store paths of enemies
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    paths[i] = get_path(u, v);
    reverse(paths[i].begin(), paths[i].end()); // Reverse for consistency
    paths[i].pop_back(); // Remove last element to prevent immediate conflict
  }

  int time = 1;
  vector<int> q, new_q; // Queue for BFS expansion
  
  can[x] = true; // Marat starts at x
  for (int u : g[x]) {
    cnt[u]++;
    q.push_back(u);
  }

  while (!can[y] && time <= n * 2) { // Simulate up to 2n steps
    time++;
    new_q.clear();
    
    // Update nodes based on current count
    for (int v : q) {
      if (can[v])
        continue;
      if (cnt[v]) {
        new_q.push_back(v);
        can[v] = true;
      }
    }
    
    q.clear();
    
    // Expand the frontiers from previous step by one more unit
    for (int v : new_q) {
      for (int u : g[v]) {
        cnt[u]++;
        q.push_back(u);
      }
    }

    // Process existing paths to adjust for conflicts and clean up
    for (int i = (int)paths.size() - 1; i >= 0; i--) {
      int v = paths[i].back();
      paths[i].pop_back();
      
      if (paths[i].empty()) {
        swap(paths[i], paths.back());
        paths.pop_back();
      }
      
      if (can[v]) { // If the vertex is occupied by an enemy
        can[v] = false;
        for (int u : g[v]) {
          cnt[u]--;
        }
        q.push_back(v);
      }
    }
  }

  if (!can[y]) {
    cout << "-1\n";
  } else {
    cout << time << "\n";
  }
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/