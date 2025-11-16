// Problem: CF 1436 B - Prime Square
// https://codeforces.com/contest/1436/problem/B

/*
Code Purpose:
This program constructs a prime square of size n x n as defined by the problem. A prime square satisfies:
1. All elements are non-negative integers <= 10^5.
2. No prime numbers appear in the square.
3. Each row and column sum is a prime number.

Algorithm:
- For n = 2, we use a fixed 2x2 pattern that ensures all row/column sums are prime (5).
- For n > 2, a cyclic pattern is used where:
  - Diagonal elements are 4.
  - Next element in cyclic order (mod n) is 1.
  - All other elements are 0.

Time Complexity: O(n^2) - We fill an n x n matrix.
Space Complexity: O(1) - No extra space needed apart from output.

Techniques:
- Mathematical construction of matrices with specific properties.
- Modular arithmetic to achieve cyclic patterns.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    if (n == 2) {
      puts("4 1\n1 4");  // Special case for 2x2 matrix
      continue;
    }
    for (long row = 0; row < n; row++) {
      for (long col = 0; col < n; col++) {
        if (col == row) {
          printf("4 ");      // Place 4 on diagonal
        } else if (col == (row + 1) % n) {
          printf("1 ");      // Place 1 in cyclic order
        } else {
          printf("0 ");      // Fill rest with 0
        }
      }
      puts("");  // Move to next line after each row
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/