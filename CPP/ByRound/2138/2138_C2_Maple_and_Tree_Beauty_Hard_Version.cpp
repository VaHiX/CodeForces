// Problem: CF 2138 C2 - Maple and Tree Beauty (Hard Version)
// https://codeforces.com/contest/2138/problem/C2

/*
 * C2. Maple and Tree Beauty (Hard Version)
 *
 * Purpose:
 *   This solution computes the maximum possible beauty of a rooted tree,
 *   where beauty is defined as the length of the longest common subsequence
 *   of names of all leaves, given that exactly k vertices are labeled '0'
 *   and the rest are labeled '1'.
 *
 * Algorithm:
 *   1. Build the tree from parent information.
 *   2. Compute depth levels and count how many nodes exist at each level.
 *   3. Reduce the counts using dynamic programming via bitset optimization,
 *      simulating subset sum operations to determine which combinations are valid.
 *   4. Apply greedy approach on the reduced items to construct a list of values
 *      representing leaf depths under various labelings.
 *   5. Use dynamic programming with bitset to determine if we can form a subset
 *      achieving specific sums.
 *
 * Time Complexity:
 *   O(n * sqrt(n)) for each test case, due to the subset sum computation
 *   performed via bitset operations with size doubling strategy.
 *
 * Space Complexity:
 *   O(n) for storing tree structure and auxiliary arrays.
 */

#include <bitset>
#include <iostream>
#include <vector>
#include <algorithm>

template <int N = 32>
int subsetsum(const std::vector<int> &a, int n, int x, int y) {
  if (n >= N) {
    return subsetsum<std::min(N << 1, 1 << 20)>(a, n, x, y); // Recursively double the bitset size when full
  }
  std::bitset<N> dp; // DP bitset tracking possible subset sums
  dp.reset();        // Initialize all bits to 0 (no subset sum achievable initially)
  dp.set(0);         // Base case: sum of zero is always achievable
  for (int i : a) {  // For each element in the input array
    dp = dp | (dp << i); // Update dp with new possible sums using left shift and OR
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
    tree[p - 1].push_back(i); // Build adjacency list for the tree
  }
  std::vector<int> d(n, 0), cnt(n, 0);
  int minLeaf = n - 1;
  for (int v = 0; v < n; ++v) {
    cnt[d[v]] += 1;        // Count nodes at each depth level
    if (tree[v].empty()) { // If current node is a leaf
      minLeaf = std::min(minLeaf, d[v]); // Track minimum leaf depth
    }
    for (int u : tree[v]) {
      d[u] = d[v] + 1;   // Assign depth to children
    }
  }
  std::vector<int> items(n + 1, 0); // Count of how many times a particular count appears
  int sum = 0;
  for (int i = 0; i <= minLeaf; ++i) {
    if (cnt[i] >= 1) {
      items[cnt[i]] += 1;  // Accumulate counts
      sum += cnt[i];
    }
  }
  std::vector<int> a;
  for (int i = 1; i <= n; ++i) {
    while (items[i] >= 3) {   // Greedily combine items to reduce total count
      items[2 * i] += 1;
      items[i] -= 2;
    }
    for (int j = 0; j < items[i]; ++j) {
      a.push_back(i);   // Generate the list of values based on frequency counts
    }
  }
  std::cout << minLeaf + subsetsum(a, sum, k, n - k) << '\n'; // Main result calculation using subsetsum
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


// https://github.com/VaHiX/CodeForces/