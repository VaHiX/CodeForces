// Problem: CF 630 F - Selection of Personnel
// https://codeforces.com/contest/630/problem/F

/*
 * Purpose: This program calculates the number of possible ways to select
 *          groups of 5, 6, and 7 people from n candidates.
 *          The result is the sum of C(n,5) + C(n,6) + C(n,7).
 *
 * Algorithms/Techniques: Combination calculation using iterative formula
 *                        to avoid large factorial computations.
 *
 * Time Complexity: O(1) - The calculation involves only a fixed number of
 *                     arithmetic operations regardless of input size.
 *
 * Space Complexity: O(1) - Only a constant amount of extra space is used.
 */

#include <stdint.h>
#include <iostream>

int main() {
  int64_t n;
  std::cin >> n;
  int64_t total(0);
  // Calculate C(n,5) * (n-4)/5
  total += (((n * (n - 1) / 2) * (n - 2) / 3) * (n - 3) / 4) * (n - 4) / 5;
  // Calculate C(n,6) * (n-5)/6
  total += ((((n * (n - 1) / 2) * (n - 2) / 3) * (n - 3) / 4) * (n - 4) / 5) *
           (n - 5) / 6;
  // Calculate C(n,7) * (n-6)/7
  total += (((((n * (n - 1) / 2) * (n - 2) / 3) * (n - 3) / 4) * (n - 4) / 5) *
            (n - 5) / 6) *
           (n - 6) / 7;
  std::cout << total << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/