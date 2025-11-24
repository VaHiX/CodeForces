// Problem: CF 1941 A - Rudolf and the Ticket
// https://codeforces.com/contest/1941/problem/A

/*
 * Problem: A. Rudolf and the Ticket
 * Purpose: Determine the number of ways to select one coin from each of two pockets such that their sum does not exceed k.
 *
 * Algorithms/Techniques:
 *   - Brute force enumeration
 *   - Nested loops to check all combinations of coins from left and right pockets
 *
 * Time Complexity: O(n * m) per test case, where n is the number of coins in left pocket and m in right pocket.
 * Space Complexity: O(n + m) for storing the arrays of coin denominations.
 */

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m, k;
    scanf("%ld %ld %ld", &n, &m, &k);
    std::vector<long> b(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &b[p]); // Read each coin denomination from left pocket
    }
    std::vector<long> c(m);
    for (long p = 0; p < m; p++) {
      scanf("%ld", &c[p]); // Read each coin denomination from right pocket
    }
    long total(0);
    for (int p = 0; p < n; p++) { // Iterate through each coin in left pocket
      for (int q = 0; q < m; q++) { // Iterate through each coin in right pocket
        if (b[p] + c[q] <= k) { // Check if the sum of coins is within budget
          ++total; // Increment count if valid combination
        }
      }
    }
    printf("%ld\n", total); // Output result for current test case
  }
}


// https://github.com/VaHiX/codeForces/