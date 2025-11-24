// Problem: CF 1360 G - A/B Matrix
// https://codeforces.com/contest/1360/problem/G

/*
 * Matrix Construction Problem (A/B Matrix)
 *
 * Purpose: Construct an n x m binary matrix where each row has exactly 'a' ones
 *          and each column has exactly 'b' ones. If impossible, output "NO".
 *
 * Algorithm:
 * - First check if a valid matrix can exist using the constraint: n * a == m * b
 * - If valid, construct the matrix using a cyclic shifting technique.
 * - Start with a string of '0's and place '1's at the beginning to satisfy row constraint.
 * - Then cyclically shift this pattern for each row to satisfy column constraints.
 *
 * Time Complexity: O(n * m) per test case
 * Space Complexity: O(m) for the string representation of each row
 */

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n, m, a, b;
    std::cin >> n >> m >> a >> b;
    if (n * a != m * b) {
      std::cout << "NO" << std::endl;
      continue;
    }
    std::cout << "YES" << std::endl;
    std::string s(m, '0');  // Initialize string of m zeros
    for (long p = 0; p < a; p++) {
      s[p] = '1';  // Place '1's at the beginning to satisfy row constraint
    }
    long shift(1);  // Determine the shift amount for cyclic rotation
    for (long p = 1; p < m; p++) {
      if ((p * n) % m == 0) {  // Find the smallest p such that (p*n) is divisible by m
        shift = p;
        break;
      }
    }
    for (long row = 0; row < n; row++) {
      std::cout << s << std::endl;
      std::string prev = s;  // Store previous row
      for (long p = 0; p < s.size(); p++) {
        s[p] = prev[(s.size() + p - shift) % s.size()];  // Perform cyclic shift
      }
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/