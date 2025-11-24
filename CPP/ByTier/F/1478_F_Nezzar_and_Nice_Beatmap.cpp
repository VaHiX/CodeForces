// Problem: CF 1478 F - Nezzar and Nice Beatmap
// https://codeforces.com/contest/1478/problem/F

/*
 * Problem: Nezzar and Nice Beatmap
 * Algorithm: Sorting by angle using dot product to ensure no angle >= 90 degrees
 *            for any three consecutive points.
 * 
 * Approach:
 * - We attempt to arrange points such that for every triplet of consecutive points,
 *   the angle at the middle point is strictly less than 90 degrees.
 * - This is checked using the dot product: if the dot product of vectors (B-A) and (C-A)
 *   is non-positive, then the angle is >= 90 degrees.
 * - We use a modified bubble sort-like approach to reorder points.
 * 
 * Time Complexity: O(n^2)
 * Space Complexity: O(n)
 */
#include <stdio.h>
#define ll (long long)
struct mp {
  int x, y, idx;
} a[5005];

// Function to check if angle at point b (between points a and c) is >= 90 degrees
// Uses dot product: if (b-a) . (c-a) <= 0, then angle >= 90
bool dot(mp a, mp b, mp c) {
  return ll(b.x - a.x) * ll(c.x - a.x) + ll(b.y - a.y) * ll(c.y - a.y) <= 0;
}

int main() {
  int n, i, j;
  mp x;
  scanf("%d", &n);
  for (i = 1; i <= n; i++)
    scanf("%d%d", &a[i].x, &a[i].y), a[i].idx = i;
  
  // Rearrange points to ensure valid order
  for (i = 3; i <= n; i++)
    for (j = i; j >= 3; j--)
      if (dot(a[j - 1], a[j], a[j - 2])) // If angle at a[j] is >= 90
        x = a[j], a[j] = a[j - 1], a[j - 1] = x; // Swap them
      else
        break; // Stop if we find a valid arrangement
  
  // Output the indices of the rearranged points
  printf("%d", a[1].idx);
  for (i = 2; i <= n; i++)
    printf(" %d", a[i].idx);
  return 0;
}


// https://github.com/VaHiX/CodeForces/