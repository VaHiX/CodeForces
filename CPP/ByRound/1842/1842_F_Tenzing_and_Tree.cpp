// Problem: CF 1842 F - Tenzing and Tree
// https://codeforces.com/contest/1842/problem/F

/*
Algorithm: Tree BFS + Dynamic Programming
Time Complexity: O(n^2)
Space Complexity: O(n)

This solution computes for each number of black vertices k (from 0 to n),
the maximum possible value of the tree when k vertices are painted black
and n-k are painted white. The value of an edge is the absolute difference
between the number of black nodes on either side after deleting the edge.

The key insight is to perform BFS from each node to compute distances,
and use these to calculate the contribution of each possible number of black nodes.
*/

#include <string.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
const int N = 5000 + 8;
int n, ans[N];
vector<int> G[N];
void bfs(int u) {
  static int q[N], dis[N];
  memset(dis, -1, sizeof dis);  // Initialize distances to -1
  q[1] = u, dis[u] = 0;         // Start BFS from node u
  for (int l = 1, r = 2; l < r; l++) {
    u = q[l];                   // Dequeue current node
    for (int v : G[u])
      if (dis[v] < 0)           // If not visited
        dis[v] = dis[u] + 1, q[r++] = v;  // Mark distance and enqueue
  }
  int sum = 0;
  for (int i = 1; i <= n; i++) {
    sum += dis[q[i]];           // Sum of distances from starting node
    ans[i] = max(ans[i], (n - 1) * i - sum * 2);  // Update maximum value for k=i
  }
}
int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);
  cin >> n;
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v, u--, v--;     // Read edges, convert to 0-based indexing
    G[u].push_back(v), G[v].push_back(u);  // Build adjacency list
  }
  for (int i = 0; i < n; i++)
    bfs(i);                     // BFS from each node to compute contributions
  for (int i = 0; i <= n; i++)
    cout << ans[i] << ' ';      // Output results for k = 0 to n
}


// https://github.com/VaHiX/CodeForces/