// Problem: CF 1895 A - Treasure Chest
// https://codeforces.com/contest/1895/problem/A

/*
 * Problem: A. Treasure Chest
 * Purpose: Find minimum time for Monocarp to open a treasure chest,
 *          given his position, chest position, key position, and stamina limit.
 *
 * Algorithms/Techniques:
 *   - Greedy simulation with conditional logic based on relative positions
 *   - Time and space complexity analysis included below
 *
 * Time Complexity: O(1) per test case (constant time operations)
 * Space Complexity: O(1) (only using a fixed number of variables)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, y, k;
    scanf("%ld %ld %ld", &x, &y, &k);
    long res(0);
    if (y <= x) {
      // If key is at or to the left of chest, no need to carry the chest past it
      res = x;
    } else if (x <= y && y <= x + k) {
      // Key is within carrying range; can pick up key on way to chest
      res = y;
    } else {
      // Key is too far; must drop chest and get key separately
      x += k;  // Move chest as far as possible within stamina limit
      res = 2 * y - x;  // Compute optimal time to reach chest after getting key
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/