// Problem: CF 2138 C2 - Maple and Tree Beauty (Hard Version)
// https://codeforces.com/contest/2138/problem/C2

/*
C2. Maple and Tree Beauty (Hard Version)
Algorithm: Dynamic Programming with Bitset Optimization + Greedy Distribution
Time Complexity: O(n * sqrt(n) * log(n)) - where n is the number of vertices.
Space Complexity: O(n * sqrt(n)) - due to bitset usage and vector storage.

The problem involves maximizing the beauty of a tree (defined as LCS of leaf names) by assigning k zeros and (n-k) ones to nodes,
with the constraint that each node's label contributes to its path from root to leaf.

Approach:
1. Build the tree from input.
2. Calculate depth levels and count how many nodes exist at each depth.
3. Distribute leaves across depths, prioritizing depth with higher counts (greedy).
4. Apply subset sum algorithm (recursively growing) to find valid assignments of node values to achieve desired k zeros.

Key Techniques:
- Bitset-based DP for fast subset sum computation, optimized recursively when needed.
- Greedy allocation based on node count per level.
- Tree traversal and assignment logic via depth levels and parent-child relationships.
*/

#include <algorithm>
#include <bitset>
#include <iostream>
#include <vector>

template <int N = 32>
int subsetsum(const std::vector<int> &a, int n, int x, int y) {
  if (n >= N) {
    return subsetsum<std::min(N << 1, 1 << 20)>(a, n, x, y); // Expand bitset size if needed
  }
  std::bitset<N> dp; // DP to track all possible subset sums up to current limit
  dp.reset();        // Reset all bits
  dp.set(0);         // Base case: sum of 0 is always achievable
  for (int i : a) {
    dp = dp | (dp << i); // Shift and or with itself to compute new reachables
  }
  for (int i = 0; i <= n; ++i) {
    if (dp.test(i) && i <= x && n - i <= y)
      return 1;
  }
  return 0;
}

void solve() {
  int n, k;
  std::cin >> n >> k;
  std::vector<std::vector<int>> tree(n);
  for (int i = 1; i < n; ++i) {
    int p;
    std::cin >> p;
    tree[p - 1].push_back(i); // Building adjacency list representation
  }
  std::vector<int> d(n, 0), cnt(n, 0);
  int minLeaf = n - 1;
  for (int v = 0; v < n; ++v) {
    cnt[d[v]] += 1;                     // Count nodes by depth
    if (tree[v].empty()) {
      minLeaf = std::min(minLeaf, d[v]); // Track minimum leaf depth
    }
    for (int u : tree[v]) {
      d[u] = d[v] + 1; // Depth assignment via BFS-like process
    }
  }
  std::vector<int> items(n + 1, 0);
  int sum = 0;
  for (int i = 0; i <= minLeaf; ++i) {
    if (cnt[i] >= 1) {
      items[cnt[i]] += 1; // Group counts by number of nodes at same depth
      sum += cnt[i];      // Sum total nodes used in this group
    }
  }

  std::vector<int> a;
  for (int i = 1; i <= n; ++i) {
    while (items[i] >= 3) {      // Greedily combine items in pairs to reduce count
      items[2 * i] += 1;
      items[i] -= 2;
    }
    for (int j = 0; j < items[i]; ++j) {
      a.push_back(i); // Add depth size to list of available elements
    }
  }

  std::cout << minLeaf + subsetsum(a, sum, k, n - k) << '\n'; // Combine best leaf count with subset matching
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t;
  std::cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/