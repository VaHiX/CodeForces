// Problem: CF 985 A - Chess Placing
// https://codeforces.com/contest/985/problem/A

/*
 * Problem: Chess Placing
 * 
 * Algorithm/Technique:
 * - The board is alternating black and white cells ('B', 'W', 'B', 'W', ...).
 * - We need to move all pieces to cells of the same color (either all black or all white).
 * - Since the positions are given, we sort them for easier processing.
 * - Two strategies are considered:
 *   1. Move all pieces to black cells (positions 1, 3, 5, ..., n-1)
 *   2. Move all pieces to white cells (positions 2, 4, 6, ..., n)
 * - For each strategy, calculate the total number of moves needed by:
 *   - Comparing each piece's current position with the target position in that color group.
 *   - Summing up the absolute differences.
 * - Return the minimum of the two totals.
 * 
 * Complexity:
 * - Time Complexity: O(n log n) due to sorting, where n is the size of the board.
 * - Space Complexity: O(n) for storing the positions of the pieces.
 */

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n / 2);  // Vector to store piece positions
  for (long p = 0; p < n / 2; p++) {
    scanf("%ld", &a[p]);
  }
  sort(a.begin(), a.end());  // Sort piece positions to facilitate grouping

  long x(0);  // Total moves to place all pieces on black cells
  for (long p = 0; p < n / 2; p++) {
    long dist = 2 * p + 2 - a[p];  // Target black cell position is 2*p + 2 (1-indexed)
    if (dist < 0) {
      dist = -dist;  // Get absolute value of distance
    }
    x += dist;
  }

  long y(0);  // Total moves to place all pieces on white cells
  for (long p = 0; p < n / 2; p++) {
    long dist = 2 * p + 1 - a[p];  // Target white cell position is 2*p + 1 (1-indexed)
    if (dist < 0) {
      dist = -dist;  // Get absolute value of distance
    }
    y += dist;
  }

  printf("%ld\n", (x < y) ? x : y);  // Print the minimum of the two options
  return 0;
}


// https://github.com/VaHiX/CodeForces/