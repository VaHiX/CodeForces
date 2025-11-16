// Problem: CF 1031 A - Golden Plate
// https://codeforces.com/contest/1031/problem/A

/*
 * Problem: Golden Plate
 * Purpose: Compute the number of cells to be gilded on a w×h rectangle with k concentric gilded rings,
 *          each ring being 1 cell wide and placed 2 cells apart from the previous one.
 * 
 * Algorithm:
 * - For each of the k rings, calculate the perimeter of the current inner rectangle.
 * - The inner rectangle for the i-th ring has dimensions (w - 4(i-1)) × (h - 4(i-1)).
 * - The number of cells in a ring is 2 * (width + height) - 4 (subtracting corners counted twice).
 * 
 * Time Complexity: O(k), as we iterate k times and perform constant-time operations.
 * Space Complexity: O(1), using only a few variables for computation.
 */

#include <cstdio>
int main() {
  long w, h, k;
  scanf("%ld %ld %ld", &w, &h, &k);
  long sum(0);  // Initialize total count of gilded cells
  while (k--) {
    sum += 2 * (w + h) - 4;  // Add perimeter of current ring (excluding corners counted twice)
    w -= 4;  // Reduce width for next inner ring
    h -= 4;  // Reduce height for next inner ring
  }
  printf("%ld\n", sum);
  return 0;
}


// https://github.com/VaHiX/codeForces/