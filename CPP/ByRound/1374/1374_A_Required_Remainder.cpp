// Problem: CF 1374 A - Required Remainder
// https://codeforces.com/contest/1374/problem/A

#include <iostream>

/*
 * Problem: Required Remainder
 * 
 * Task: Given integers x, y, and n, find the maximum integer k such that:
 *       0 <= k <= n and k % x == y.
 * 
 * Algorithm:
 *   - The largest number <= n with remainder y when divided by x is:
 *     ((n - y) / x) * x + y
 *   - This computes the largest multiple of x that is <= (n - y), then adds y.
 * 
 * Time Complexity: O(t), where t is the number of test cases
 * Space Complexity: O(1)
 */

int main() {
  int t, x, y, n;
  for (std::cin >> t; t--;) {
    std::cin >> x >> y >> n, std::cout << ((n - y) / x) * x + y << '\n'; // Compute max k with remainder y
  }
}

// https://github.com/VaHiX/codeForces/