// Problem: CF 2117 F - Wildflower
// https://codeforces.com/contest/2117/problem/F

/*
F. Wildflower
time limit per test2 seconds
memory limit per test256 megabytes

Task: Count the number of ways to assign values 1 or 2 to each node of a tree such that all subtree sums are unique.

Algorithms/Techniques:
- Tree DFS traversal
- Dynamic programming on trees
- Modular arithmetic for large results

Time Complexity: O(n) per test case, where n is the number of nodes.
Space Complexity: O(n) for storing the tree structure and recursion stack.

*/

#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
const int kMaxN = 2e5 + 1, mod = 1e9 + 7;
int t, n, c, o, p, q, ans;
vector<int> e[kMaxN];

void dfs(int x, int f, int d) {
  // Count leaf nodes (nodes with only one neighbor, excluding parent)
  // Also track depth and accumulate depths for specific calculations
  e[x].size() == (f > 0) && (c++, o = d, p += d),
      e[x].size() == 2 + (f > 0) && (q = d);
  for (int i : e[x]) {
    if (i != f) {
      dfs(i, x, d + 1); // Continue DFS with increased depth
    }
  }
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  for (cin >> t; t--;) {
    cin >> n, p = c = 0;
    for (int i = 1, x, y; i < n; i++) {
      cin >> x >> y, e[x].push_back(y), e[y].push_back(x); // Build adjacency list
    }
    dfs(1, 0, 1); // Start DFS from root node with depth 1
    
    if (c > 2) {
      ans = 0; // If more than two leaves exist, impossible to have all distinct sums
    } else if (c == 1) {
      ans = 1;
      for (int i = 1; i <= n; i++) {
        ans *= 2, ans >= mod && (ans -= mod); // Each node can be 1 or 2 => 2^n combinations
      }
    } else {
      p -= o, ans = 1; // Adjust accumulated depth
      for (int i = 1; i <= q + max(0, abs(o - p) - 1); i++) {
        ans *= 2, ans >= mod && (ans -= mod); // Multiply by power of 2 for valid configurations
      }
      ans = ans * (o != p ? 3ll : 2ll) % mod; // Apply special rule for two leaves case
    }
    cout << ans << '\n', fill(e + 1, e + n + 1, vector<int>()); // Output and reset adjacency lists
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/