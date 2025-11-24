// Problem: CF 1555 C - Coin Rows
// https://codeforces.com/contest/1555/problem/C

/*
C. Coin Rows
Alice and Bob are playing a game on a matrix, consisting of 2 rows and m columns.
Initially, both start at cell (1, 1) and must reach (2, m).
Alice moves first, collecting coins along her path.
Then Bob moves, collecting coins that he visits but Alice did not.
The goal is to find the optimal score when both play optimally.

Algorithm:
- Precompute prefix sums for each row (right-to-left for row 0, left-to-right for row 1).
- For each possible point where Alice's path might change direction (from row 1 to row 2),
  calculate how many coins Bob can collect.
- Use dynamic programming approach to compute optimal score.

Time Complexity: O(n) per test case
Space Complexity: O(n) for the 2D vector storing the matrix and prefix sums
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<std::vector<long>> f(2, std::vector<long>(n, 0));
    for (long row = 0; row < 2; row++) {
      for (long col = 0; col < n; col++) {
        scanf("%ld", &f[row][col]);
      }
    }
    // Compute suffix sums for row 0 (from right to left)
    for (long p = n - 2; p >= 0; p--) {
      f[0][p] += f[0][p + 1];
    }
    // Compute prefix sums for row 1 (from left to right)
    for (long p = 1; p < n; p++) {
      f[1][p] += f[1][p - 1];
    }
    long res(2e9);
    for (long p = 0; p < n; p++) {
      // u: coins Bob collects on the right side of Alice's path in row 0
      long u = (p + 1 < n) ? f[0][p + 1] : 0;
      // v: coins Bob collects on the left side of Alice's path in row 1
      long v = (p > 0) ? f[1][p - 1] : 0;
      // w: maximum of u and v (Bob wants to maximize)
      long w = (u > v) ? u : v;
      // res: minimum score for Alice (minimize Bob's max gain)
      res = (res < w) ? res : w;
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/