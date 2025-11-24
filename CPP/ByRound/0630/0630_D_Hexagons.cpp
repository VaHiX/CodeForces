// Problem: CF 630 D - Hexagons!
// https://codeforces.com/contest/630/problem/D

#include <stdint.h>
#include <iostream>

/*
 * D. Hexagons!
 * Purpose: Calculate the number of hexagonal cells within distance n from a central hexagon.
 * Algorithm: Mathematical formula derived from hexagonal lattice properties.
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 *
 * The problem involves counting hexagons in a hexagonal grid within a certain distance.
 * For a hexagon at distance n, the total count follows the formula:
 * 3 * n * (n + 1) + 1
 * This accounts for layers of hexagons around the central one.
 */

int main() {
  int64_t n;
  std::cin >> n;  // Read input distance n
  int64_t res = 3 * n * (n + 1) + 1;  // Apply formula to compute number of hexagons
  std::cout << res << std::endl;  // Output result
  return 0;
}

// https://github.com/VaHiX/codeForces/