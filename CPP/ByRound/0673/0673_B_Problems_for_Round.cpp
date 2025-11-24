// Problem: CF 673 B - Problems for Round
// https://codeforces.com/contest/673/problem/B

/*
 * Purpose: This program determines the number of ways to split n problems
 *          into two divisions such that:
 *          1. Each division has at least one problem.
 *          2. Each problem is assigned to exactly one division.
 *          3. All problems in division 1 are harder than those in division 2.
 *          4. Similar problems must be in different divisions.
 *
 *          The key insight is that we can only split the problems at a point
 *          where no similar pair crosses the boundary. This means we want 
 *          to find the minimum and maximum indices of similar pairs, and 
 *          the number of valid split points is the number of positions 
 *          between these indices.
 *
 * Time Complexity: O(m), where m is the number of similar pairs.
 * Space Complexity: O(1), only using a constant amount of extra space.
 */
#include <cstdio>
int main() {
  long n, m;
  scanf("%ld %ld\n", &n, &m);
  long min(n), max(1);
  while (m--) {
    long x, y;
    scanf("%ld %ld\n", &x, &y);
    if (y < x) {
      long temp = x;
      x = y;
      y = temp;
    }
    if (max < x) {
      max = x;
    }
    if (y < min) {
      min = y;
    }
  }
  printf("%ld\n", (max < min) ? (min - max) : 0);
  return 0;
}


// https://github.com/VaHiX/CodeForces/