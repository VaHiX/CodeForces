// Problem: CF 1452 A - Robot Program
// https://codeforces.com/contest/1452/problem/A

/*
 * Problem: Robot Program
 * Purpose: Find minimum number of commands for a robot to reach (x, y) from (0, 0)
 *          with no consecutive repeated commands.
 * Algorithms/Techniques: Mathematical approach using Manhattan distance and optimization
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 *
 * The key insight is that we need to move x units east and y units north (or vice versa).
 * The minimal path uses alternating movements, with special handling for when x == y.
 * The formula derived is:
 *   res = 2 * max(x, y) - (x != y)
 * This accounts for:
 *   - Moving in the larger direction twice (once to go and once to return if needed)
 *   - Subtracting 1 if x != y (since we can avoid one extra step when they're equal)
 */
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    long res = 2 * (x > y ? x : y) - (x != y); // Calculate minimum steps using formula
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/