// Problem: CF 858 A - k-rounding
// https://codeforces.com/contest/858/problem/A

/*
 * Problem: k-rounding
 * 
 * Given a positive integer n and a non-negative integer k, find the minimum
 * positive integer x such that:
 *   1. x ends with k or more zeros
 *   2. x is divisible by n
 * 
 * Algorithm:
 *   - To ensure x ends with k zeros, it must be divisible by 10^k.
 *   - Hence, x must be a multiple of both n and 10^k.
 *   - The smallest such x is the LCM of n and 10^k.
 *   - LCM(a,b) = (a * b) / GCD(a,b)
 *   - So, we compute LCM(n, 10^k) = (n * 10^k) / GCD(n, 10^k)
 * 
 * Time Complexity: O(log(min(n, 10^k))) = O(log n)
 * Space Complexity: O(1)
 */

#include <stdint.h>
#include <iostream>

long gcd(int64_t a, int64_t b) { return (b == 0) ? a : gcd(b, a % b); }
int main() {
  int64_t n, k;
  std::cin >> n >> k;
  int64_t m = 1;
  for (int p = 0; p < k; p++) {
    m *= 10;
  }
  int64_t g = gcd(m, n);
  int64_t res = (n / g) * m; // Compute LCM(n, m) = (n * m) / GCD(n, m)
  std::cout << res << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/