// Problem: CF 1368 C - Even Picture
// https://codeforces.com/contest/1368/problem/C

/*
 * Problem: C. Even Picture
 * Purpose: Construct a "beautiful" picture with exactly n gray cells that have all gray neighbors.
 *          A picture is beautiful if:
 *          1. It is connected (all gray cells are reachable from each other)
 *          2. Each gray cell has an even number of gray neighbors
 *          3. Exactly n gray cells have all gray neighbors (i.e., they are adjacent to only gray cells)
 *
 * Algorithm:
 * - Start with a small base structure that satisfies the constraints.
 * - Add a chain of cells to ensure we have n such special cells.
 * - Place the base 4 cells forming a 2x2 square.
 * - For each of the n required cells, place three additional cells in a pattern,
 *   forming a "staircase-like" structure that ensures connectivity and even-degree neighbors.
 * 
 * Time Complexity: O(n) - linear in the input n.
 * Space Complexity: O(n) - for storing the coordinates of the gray cells.
 */

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  printf("%ld\n", 4 + 3 * n);  // Total number of gray cells = base 4 + 3 * n
  puts("0 0");                 // First base cell
  puts("0 1");                 // Second base cell
  puts("1 0");                 // Third base cell
  puts("1 1");                 // Fourth base cell
  for (long p = 0; p < n; p++) {
    printf("%ld %ld\n", p + 1, p + 2);  // Place cells to form the pattern
    printf("%ld %ld\n", p + 2, p + 1);  // Ensure even degree for all cells
    printf("%ld %ld\n", p + 2, p + 2);  // Maintain connectivity and property
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/