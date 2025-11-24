// Problem: CF 1029 E - Tree with Small Distances
// https://codeforces.com/contest/1029/problem/E

/*
E. Tree with Small Distances
Algorithms/Techniques: DFS traversal on tree, greedy approach to minimize added edges
Time Complexity: O(n)
Space Complexity: O(n)

Task:
Add minimum number of edges such that every vertex is at distance at most 2 from vertex 1.

Approach:
- Perform DFS starting from node 1
- For each node, compute the maximum distance to its descendants
- If a descendant is at distance > 2 from root, we must add an edge from current node to that descendant (or one of its ancestors)
- Count such needed edges greedily

Note: This code attempts to solve the problem but contains logic errors in how it computes distances.
The implementation does not correctly handle the greedy edge addition. A correct and simpler approach would be:
1. Find all nodes at distance 3 or more from root (node 1).
2. For each such node, we need to add an edge from its ancestor at distance 2 from root.
3. Count such needed edges using a greedy selection of ancestors.
*/
#include <iostream>
#include <vector>
#include <algorithm>

#define Fast                                                                   \
  ios::sync_with_stdio(0);                                                     \
  cin.tie(0);                                                                  \
  cout.tie(0);
using namespace std;
#define int long long
#define pb push_back
const int N = 200002;
vector<int> g[N]; // adjacency list
int n, ans, dis[N]; // answer counter and distance array

void dfs(int u, int p) {
  for (auto to : g[u]) { // iterate through neighbors
    if (to == p) // skip parent to avoid going back
      continue;
    dis[to] = dis[u] + 1; // set distance of neighbor to parent's distance + 1
    dfs(to, u); // recursive DFS call
    if (dis[to] > 2) { // if descendant is beyond distance 2
      ++ans; // increment answer
      dis[u] = 1; // reset distance of current node to 1 (because we added edge)
    }
    dis[u] = min(dis[to] + 1, dis[u]); // keep track of min distance from current node
  }
}

signed main() {
  Fast;
  cin >> n;
  for (int i = 1; i < n; ++i) { // read all edges
    int a, b;
    cin >> a >> b;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  dfs(1, 0); // start DFS from node 1 with no parent (0)
  cout << ans << endl; // output result
  return 0;
}


// https://github.com/VaHiX/codeForces/