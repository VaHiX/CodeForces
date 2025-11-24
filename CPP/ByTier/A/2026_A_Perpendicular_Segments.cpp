// Problem: CF 2026 A - Perpendicular Segments
// https://codeforces.com/contest/2026/problem/A

/*
 * Problem: Perpendicular Segments
 *
 * Task: Given X, Y, and K, find two integer-coordinate line segments AB and CD
 *       such that:
 *       - Both segments are within bounds [0,X] x [0,Y]
 *       - Length of AB >= K
 *       - Length of CD >= K
 *       - Segments AB and CD are perpendicular (lines they induce are perpendicular)
 *
 * Algorithm:
 *   - For any valid input, we can construct a solution by using the following:
 *     - First segment: from (0, 0) to (m, 0), where m = min(X, Y)
 *     - Second segment: from (0, 0) to (0, m)
 *   - This ensures both segments have length m, and since one is horizontal
 *     and the other is vertical, they are perpendicular.
 *   - Since the constraint guarantees a valid solution, we can always set m = min(X, Y),
 *     ensuring both segments are within bounds.
 *
 * Time Complexity: O(1) - constant time per test case.
 * Space Complexity: O(1) - constant space usage.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, y, k;
    scanf("%ld %ld %ld", &x, &y, &k);
    long m = (x < y ? x : y);  // Determine the maximum possible segment length
    printf("0 0 %ld %ld\n0 %ld %ld 0\n", m, m, m, m);  // Output the two perpendicular segments
  }
}


// https://github.com/VaHiX/CodeForces/