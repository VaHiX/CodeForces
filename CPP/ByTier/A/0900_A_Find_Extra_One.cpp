// Problem: CF 900 A - Find Extra One
// https://codeforces.com/contest/900/problem/A

/*
 * Problem: Find Extra One
 * 
 * Purpose:
 *   Determines if there exists a point such that after its removal,
 *   all remaining points lie on one side of the Y-axis (OY axis).
 * 
 * Algorithm:
 *   - Count how many points have positive x-coordinate (pos)
 *   - Count how many points have negative x-coordinate (neg)
 *   - If either count is <= 1, then removing that point will leave
 *     all other points on one side of the Y-axis.
 * 
 * Time Complexity: O(n)
 *   - Single pass through all n points to count positive and negative x-values.
 * 
 * Space Complexity: O(1)
 *   - Only using a constant amount of extra space for counters.
 */

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  long pos(0), neg(0); // Count of points with positive and negative x-coordinates
  while (n--) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    pos += (x > 0);   // Increment pos if x > 0
    neg += (x < 0);   // Increment neg if x < 0
  }
  puts((pos <= 1 || neg <= 1) ? "Yes" : "No"); // Output "Yes" if at most one point on either side
  return 0;
}


// https://github.com/VaHiX/CodeForces/