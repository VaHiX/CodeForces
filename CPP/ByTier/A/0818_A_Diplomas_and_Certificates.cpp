// Problem: CF 818 A - Diplomas and Certificates
// https://codeforces.com/contest/818/problem/A

/*
 * Code Purpose:
 * This code solves the problem of distributing diplomas and certificates among students
 * such that:
 * 1. The number of certificates is exactly k times the number of diplomas.
 * 2. The total number of winners (diplomas + certificates) is at most n/2.
 * 3. The number of winners is maximized.
 *
 * Algorithm:
 * - Let 'a' be the number of diplomas.
 * - Let 'b' be the number of certificates.
 * - From the constraints:
 *   - b = k * a
 *   - a + b <= n / 2
 *   - Substituting b: a + k * a <= n / 2 => a * (1 + k) <= n / 2
 *   - So, a <= (n / 2) / (k + 1)
 * - We maximize 'a', then compute 'b' and 'c' (non-winners).
 *
 * Time Complexity: O(1) - constant time operations.
 * Space Complexity: O(1) - only using a few integer variables.
 */

#include <stdint.h>
#include <iostream>

int main() {
  int64_t n, k;
  std::cin >> n >> k;
  // Calculate maximum number of diplomas (a)
  // a * (k + 1) <= n / 2 => a <= (n / 2) / (k + 1)
  int64_t a = (n / 2) / (k + 1);
  // Number of certificates is k times number of diplomas
  int64_t b = k * a;
  // Remaining students are not winners
  int64_t c = n - a - b;
  std::cout << a << " " << b << " " << c << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/