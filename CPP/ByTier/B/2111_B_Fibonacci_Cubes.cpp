// Problem: CF 2111 B - Fibonacci Cubes
// https://codeforces.com/contest/2111/problem/B

/*
B. Fibonacci Cubes
Algorithm: For each test case, precompute the first n+1 Fibonacci numbers (f_1 to f_{n+1}) to determine cube sizes.
For each box, check whether all cubes fit by verifying that the largest dimension of the box is at least as large as the largest cube (f_{n+1}), 
and the sum of the two smaller dimensions of the box is at least as large as the second largest cube (f_n).

Time Complexity: O(n + m) per test case, where n is the number of cubes and m is the number of boxes.
Space Complexity: O(1) for computation (excluding input/output), since we only store a few Fibonacci numbers and the result string.

*/
#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n, m;
    std::cin >> n >> m;
    long f(1), g(1);  // Initialize first two Fibonacci numbers
    for (long p = 2; p <= n + 1; p++) {  // Compute up to f_{n+1}
      long x = f;
      f = g;
      g += x;  // f becomes previous g, g becomes sum of old f and g
    }
    std::string s(m, '0');  // Initialize result string with '0'
    for (long p = 0; p < m; p++) {  // Process each box
      long a, b, c;
      std::cin >> a >> b >> c;
      long d = (a > b ? a : b);  // Find max of a and b
      d = (d > c ? d : c);       // Find max among all three dimensions
      s[p] += (a >= f && b >= f && c >= f && d >= g);  // Check if all cubes fit
    }
    std::cout << s << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/