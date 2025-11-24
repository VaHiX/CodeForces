// Problem: CF 1257 A - Two Rival Students
// https://codeforces.com/contest/1257/problem/A

/*
 * Problem: A. Two Rival Students
 * Purpose: Maximize the distance between two rival students in a row by swapping adjacent students.
 * Algorithm: 
 *   - Calculate initial distance between the two students.
 *   - Try to move both students as far apart as possible using at most x swaps.
 *   - The maximum possible distance is min(n-1, original_distance + x).
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, x, a, b;
    scanf("%ld %ld %ld %ld", &n, &x, &a, &b);
    long d = b - a; // Calculate difference between positions
    if (d < 0) {
      d = -d; // Make sure distance is positive
    }
    d += x; // Add possible moves to the distance
    if (d > n - 1) {
      d = n - 1; // Cap the maximum possible distance at n-1
    }
    printf("%ld\n", d);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/