// Problem: CF 476 C - Dreamoon and Sums
// https://codeforces.com/contest/476/problem/C

/*
 * C. Dreamoon and Sums
 *
 * Problem Description:
 * Given two integers a and b, we need to compute the sum of all "nice" integers.
 * A positive integer x is called "nice" if for some integer k in [1, a], 
 * (x / k) mod b == 0, where / denotes integer division.
 *
 * Algorithm:
 * The solution uses mathematical derivation to compute the result efficiently.
 * It calculates two components:
 * - resultA = (b * (b - 1) / 2) % M
 * - resultB = (a + ((a * (a + 1) / 2) % M) * b) % M
 * Then computes final result as (resultA * resultB) % M.
 *
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */

#include <stdint.h>
#include <iostream>

int main() {
  const int64_t M = 1000000007; // Modulo value
  int64_t a, b;
  std::cin >> a >> b;
  
  // Calculate resultA using arithmetic progression formula
  int64_t resultA = (b * (b - 1) / 2) % M;
  
  // Calculate resultB with modular arithmetic
  int64_t resultB = (a + ((a * (a + 1) / 2) % M) * b) % M;
  
  // Final result is product of resultA and resultB modulo M
  int64_t result = (resultA * resultB) % M;
  std::cout << result << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/