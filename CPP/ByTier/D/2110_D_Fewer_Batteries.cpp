// Problem: CF 2110 D - Fewer Batteries
// https://codeforces.com/contest/2110/problem/D

/*
D. Fewer Batteries
Algorithm: Binary search on the answer + Dynamic Programming with graph traversal
Time Complexity: O((n + m) * log(1e9))
Space Complexity: O(n + m)

This problem involves finding the minimum number of batteries required for a robot 
to travel from checkpoint 1 to checkpoint n in a directed acyclic graph where:
- Each node has some batteries available.
- Each edge requires a minimum number of batteries to traverse.
- At each node, robots can collect all available batteries (and carry them forward).
The solution uses binary search on the answer combined with a DP-based BFS check.

Key techniques used:
- Binary search over possible battery values
- Dynamic Programming with graph traversal using topological order
*/

#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;
vector<pair<int, int>> Map[200005]; // Adjacency list: {to_node, required_batteries}
int n, val[200005], dp[200005];     // val[i]: batteries at node i, dp[i]: max batteries collected so far at node i

// Function to check if we can reach node n with k batteries at start
int topology(int k) {
  for (int i = 1; i <= n; i++)
    dp[i] = 0;
  for (int u = 1; u < n; u++) {         // Iterate through nodes in topological order
    if (u != 1 && !dp[u])              // Skip unvisited nodes except root
      continue;
    dp[u] = min(k, dp[u] + val[u]);    // Update batteries collected at node u, capped by k
    for (auto [v, w] : Map[u]) {       // For each neighbor of u
      if (dp[u] >= w)                  // If we have enough batteries to go to v
        dp[v] = max(dp[v], dp[u]);     // Update max batteries at v
    }
  }
  return dp[n];  // Return number of batteries at destination node
}

int main() {
  int T, m, a, b, w;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
      scanf("%d", val + i);             // Read number of batteries at each node
    for (int i = 0; i < m; i++) {
      scanf("%d %d %d", &a, &b, &w);    // Read edge: a -> b with weight w
      Map[a].push_back({b, w});        // Build adjacency list
    }
    
    int l = 1, r = 1e9, mid;
    while (l <= r) {
      mid = (l + r) / 2;               // Binary search for minimum answer
      if (topology(mid))               // If we can reach destination with 'mid' batteries
        r = mid - 1;                   // Try smaller value
      else
        l = mid + 1;                   // Else try larger value
    }
    
    printf("%d\n", l == 1e9 + 1 ? -1 : l); // Print result or -1 if impossible
    
    for (int i = 1; i <= n; i++)
      Map[i].clear();                  // Clear adjacency list for next test case
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/