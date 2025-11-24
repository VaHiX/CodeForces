// Problem: CF 1716 A - 2-3 Moves
// https://codeforces.com/contest/1716/problem/A

/*
 * Problem: Minimum Moves to Reach Point n
 * Algorithm: Greedy approach based on modular arithmetic
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 *
 * Explanation:
 * We can move 2 or 3 units in each step (either left or right).
 * To minimize steps, we want to use the largest possible moves (3s) where feasible.
 * The key insight is based on n % 3:
 * - If n % 3 == 0: Use n/3 moves of 3
 * - If n % 3 == 1: Use one move of 2, then (n-4)/3 moves of 3 (this requires at least 4 to be valid)
 * - If n % 3 == 2: Use one move of 2 and (n-2)/3 moves of 3
 * Special case when n == 1: Need 2 moves (1 move of 2)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long res(0);
    if (n == 1) {
      res = 2; // Special case: 1 step of 2 to reach 2, then 1 step back to 1
    } else if (n % 3 == 0) {
      res = n / 3; // All steps of 3
    } else if (n % 3 == 1) {
      res = 2 + ((n - 4) / 3); // One step of 2, then (n-4)/3 steps of 3
    } else if (n % 3 == 2) {
      res = 1 + (n / 3); // One step of 2, then n/3 steps of 3
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/