// Problem: CF 1873 B - Good Kid
// https://codeforces.com/contest/1873/problem/B

/*
B. Good Kid
Purpose: Given an array of digits, find the maximum product possible by adding 1 to exactly one digit.
Algorithm:
- For each test case, compute the product of all digits.
- Track the smallest non-zero digit (m) and count zeros (z).
- If there are more than one zero, the result is 0.
- If there is exactly one zero, the result is the product of all non-zero elements.
- If there are no zeros, multiply the product by (m + 1) / m to simulate adding 1 to the smallest digit.

Time Complexity: O(n) per test case, where n is the number of digits.
Space Complexity: O(1), only using a few variables for computation.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    int n;
    scanf("%d", &n);
    long long prod(1); // Initialize product of all non-zero elements
    int m(10), z(0);   // m tracks the smallest non-zero digit, z counts zeros
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x == 0) {
        ++z;           // Increment zero counter
        continue;
      }
      prod *= x;       // Multiply current element to the product
      if (x < m) {
        m = x;         // Update smallest non-zero digit
      }
    }
    if (z > 1) {
      puts("0");       // More than one zero: product is always zero
    } else if (z == 1) {
      printf("%lld\n", prod); // Exactly one zero: result is the product of all non-zero elements
    } else {
      printf("%lld\n", prod * (m + 1) / m); // No zeros: add 1 to smallest element for max gain
    }
  }
}


// https://github.com/VaHiX/codeForces/