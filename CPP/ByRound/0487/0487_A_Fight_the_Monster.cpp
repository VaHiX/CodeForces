// Problem: CF 487 A - Fight the Monster
// https://codeforces.com/contest/487/problem/A

#include <cstdio>
#include <algorithm>

/*
 * Algorithm: Brute-force search with optimization
 * Purpose: Find minimum bitcoins needed for Master Yang to defeat the monster.
 * 
 * Time Complexity: O(1) - since the loops are bounded by fixed constants (200 and 100),
 *                    independent of input size.
 * Space Complexity: O(1) - only a few integer variables are used.
 * 
 * Techniques:
 * - Exhaustive search over possible ATK and DEF purchases.
 * - Helper function to compute required HP using mathematical formula.
 * - Optimization by limiting search space based on problem constraints.
 */

// Helper function to calculate the minimum HP Yang needs to win
// Returns a large value if Yang cannot win with current ATK/DEF
int findHp(int hy, int ay, int dy, int hm, int am, int dm) {
  if (dm >= ay) {
    return 1e7; // Yang cannot win, return large number
  }
  // Calculate how many hits Yang must land
  // (hm + ay - dm - 1) / (ay - dm) gives rounds needed for Yang to kill monster
  // Multiply by damage per round (am - dy) and add 1 for safety margin
  return ((hm + ay - dm - 1) / (ay - dm)) * (am - dy) + 1;
}

int main() {
  int hy, ay, dy;
  scanf("%d %d %d\n", &hy, &ay, &dy); // Read Yang's stats
  int hm, am, dm;
  scanf("%d %d %d\n", &hm, &am, &dm); // Read monster's stats
  int hc, ac, dc;
  scanf("%d %d %d\n", &hc, &ac, &dc); // Read prices

  long res(1e7); // Initialize result to a large value

  // Loop through possible number of ATK and DEF buys (bounded)
  for (int abuy = 200; abuy >= 0; abuy--) {
    for (int dbuy = 100; dbuy >= 0; dbuy--) {
      // Compute cost of current ATK and DEF purchases
      int cur = abuy * ac + dbuy * dc;

      // Calculate required HP for Yang to survive
      int neededHp = std::max(findHp(hy, ay + abuy, dy + dbuy, hm, am, dm) - hy, 0);

      // Add cost of required HP
      cur += neededHp * hc;

      // Update result if current is better
      res = (res < cur) ? res : cur;
    }
  }

  printf("%ld\n", res); // Output the minimum cost
  return 0;
}


// https://github.com/VaHiX/CodeForces/