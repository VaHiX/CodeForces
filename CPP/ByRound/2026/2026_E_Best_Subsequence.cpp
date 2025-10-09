// Problem: CF 2026 E - Best Subsequence
// https://codeforces.com/contest/2026/problem/E

/*
E. Best Subsequence

Algorithm: Maximum Independent Set on a Bipartite Graph using Maximum Matching (König's Theorem)
- Each element of the array is treated as a left node in a bipartite graph.
- Each possible bit position (1 to 61) is treated as a right node.
- An edge exists between an element and a bit if that bit is set in the element.
- The problem reduces to finding the maximum matching in this bipartite graph.
- The answer is n minus the size of the maximum matching, which gives the minimum vertex cover.

Time Complexity: O(n * 61 * n) = O(n^2), since we run DFS for each node and DFS can go up to n steps.
Space Complexity: O(n * 61) = O(n), for the adjacency list representation of the graph.

*/

#include <string.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
const int kN = 105;
bool vis[kN];                     // Visited array for DFS traversal
vector<int> e[kN];                // Adjacency list for bipartite graph
int T, n, ans;                    // Test cases, number of elements, matching count
int m[kN];                        // m[i] stores which node (element) is matched to bit i

bool DFS(int x) {                 // Find augmenting path starting from element x
  for (int i : e[x]) {            // For each bit position connected to element x
    if (!vis[i]) {                // If the bit hasn't been visited yet
      vis[i] = 1;                 // Mark it as visited
      if (!m[i] || DFS(m[i])) {   // If no match or can find augmenting path
        m[i] = x;                 // Match x to this bit
        return 1;                 // Path found
      }
    }
  }
  return 0;                       // No augmenting path
}

void Clear() {                    // Reset graph and matching for next test case
  for (int i = 1; i <= n; i++) {
    e[i].clear();
  }
  memset(m, 0, sizeof(m));
  ans = 0;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (cin >> T; T--; Clear()) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      ll x;
      cin >> x;
      for (int j = 1; j <= 61; j++) {  // For each possible bit position
        if (x >> (j - 1) & 1) {         // If j-th bit is set in x
          e[i].push_back(j);            // Connect element i to bit j
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      memset(vis, 0, sizeof(vis));   // Reset visited array for each DFS start
      ans += DFS(i);                 // Try to find augmenting path from element i
    }
    cout << n - ans << '\n';         // Minimum vertex cover = n - max matching
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/