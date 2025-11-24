// Problem: CF 1674 G - Remove Directed Edges
// https://codeforces.com/contest/1674/problem/G
 
/*
Algorithm/Technique: 
- The problem is to find the maximum size of a "cute" set in a DAG after removing some edges.
- A "cute" set means that every pair of vertices in the set is connected by a path in either direction using remaining edges.
- This is essentially finding the size of the largest strongly connected component (SCC) in the graph, but since it's a DAG, we must be more careful.
- The solution involves a DFS-based approach where we compute a value dp[u] that represents the maximum number of vertices in a cute set rooted at u.
- The key insight is:
    - If a vertex u has outdegree > 1, it can potentially connect to multiple children.
    - If a child v has indegree >= 2, we can consider combining paths from v into u's path.
    - The DFS processes nodes in a way that ensures we don't double-count or miss components.
- Time Complexity: O(n + m), since each node and edge is visited a constant number of times.
- Space Complexity: O(n + m), for storing the graph and auxiliary arrays.
*/
 
#include <algorithm>
#include <iostream>
#include <vector>
 
using namespace std;
const int N = 2e5 + 10;
int in[N], out[N];         // in[v] and out[v] store indegree and outdegree of vertex v
int dp[N];                 // dp[u] stores max size of cute set starting from vertex u
vector<int> g[N];          // adjacency list representation of the graph
int n, m;
 
void dfs(int u) {
  // If already computed, return early
  if (dp[u])
    return;
  
  // Mark current node as visited
  dp[u] = 1;
  
  // If outdegree is 1 or less, no further combining possible
  if (out[u] <= 1) {
    return;
  }
  
  // Visit all neighbors
  for (int v : g[u]) {
    dfs(v);  // Recursively process child
    
    // If child has indegree >= 2, it can contribute to a larger cute set
    if (in[v] >= 2) {
      dp[u] = max(dp[v] + 1, dp[u]);  // Update dp[u] with better value
    }
  }
}
 
int main() {
  cin >> n >> m;
  
  // Read edges and update in/out degrees
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);     // Add edge u -> v
    in[v]++, out[u]++;     // Increment indegree of v and outdegree of u
  }
  
  // Start DFS from each node to compute dp values
  for (int i = 1; i <= n; i++)
    dfs(i);
  
  // Print the maximum value in dp array
  cout << *max_element(dp + 1, dp + 1 + n);
}
 
 
// https://github.com/VaHiX/CodeForces/