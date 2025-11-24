// Problem: CF 2074 F - Counting Necessary Nodes
// https://codeforces.com/contest/2074/problem/F

/*
F. Counting Necessary Nodes

Purpose:
This code determines the minimum number of quadtree nodes needed to represent a given rectangular region [l1, r1] × [l2, r2].
The algorithm works by recursively dividing the region into smaller quadrants and counting the necessary nodes.

Algorithms/Techniques:
- Quadtree decomposition with recursive subdivision
- Bit manipulation optimization for efficient coordinate reduction

Time Complexity: O(log(max(r1, r2)))
Space Complexity: O(1)

Input:
Each test case contains four integers l1, r1, l2, r2 representing the boundaries of a rectangular region.

Output:
For each test case, output the minimum number of nodes needed to cover the given region exactly.
*/

#include <iostream>

void solve() {
  int l1, r1, l2, r2;
  std::cin >> l1 >> r1 >> l2 >> r2;
  long long res = 1ll * (r1 - l1) * (r2 - l2); // Initialize with total area
  while (true) {
    l1 = (l1 + 1) / 2; // Move to next level in quadtree for x-axis
    r1 /= 2;           // Move to next level in quadtree for x-axis
    l2 = (l2 + 1) / 2; // Move to next level in quadtree for y-axis
    r2 /= 2;           // Move to next level in quadtree for y-axis
    if (l1 == r1 || l2 == r2) { // If we've reached leaf nodes
      break;
    }
    res -= 3ll * (r1 - l1) * (r2 - l2); // Subtract overlapping areas from parent level
  }
  std::cout << res << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int t;
  std::cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/