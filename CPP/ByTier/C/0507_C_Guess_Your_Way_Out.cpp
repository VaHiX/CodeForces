// Problem: CF 507 C - Guess Your Way Out!
// https://codeforces.com/contest/507/problem/C

/*
 * Problem: Guess Your Way Out!
 * Algorithm: Binary Tree Traversal Simulation
 * Purpose: Calculate the number of nodes visited before reaching the exit in a perfect binary tree,
 *          following a specific traversal algorithm based on an infinite "LRLRLR..." pattern.
 *
 * Time Complexity: O(h), where h is the height of the tree.
 * Space Complexity: O(h), for storing the binary representation of the node index.
 */

#include <cstdio>
#include <vector>
int main() {
  long long h, n;
  scanf("%lld %lld\n", &h, &n);
  --n; // Convert to 0-based indexing
  std::vector<int> bits(h, 0); // Store binary representation of n
  for (long long p = 0; p < h; p++) {
    bits[p] = n % 2;  // Extract least significant bit
    n /= 2;           // Shift right by 1 bit
  }
  long long ans(0);
  bool k(0); // Tracks the expected direction ('L' or 'R') at current level
  for (int p = h - 1; p >= 0; p--) {
    if (bits[p] != k) {
      // If the bit doesn't match expected direction, we need to go down and then back up
      ans += (1LL << (p + 1)); // Add the number of nodes in the subtree
    } else {
      // If the bit matches, we take a step in the direction and update expected direction
      ++ans;
      k = 1 - k; // Toggle expected direction
    }
  }
  printf("%lld\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/