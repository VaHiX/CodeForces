// Problem: CF 1985 B - Maximum Multiple Sum
// https://codeforces.com/contest/1985/problem/B

/*
B. Maximum Multiple Sum
Algorithm: Mathematical observation
Time Complexity: O(1) per test case
Space Complexity: O(1)

For each n, we need to find x such that the sum of multiples of x up to n is maximized.
The sum of multiples of x less than or equal to n is:
x + 2x + 3x + ... + kx = x * (1 + 2 + ... + k) = x * k * (k + 1) / 2
where k = floor(n / x).

By mathematical analysis, it can be shown that the maximum sum is achieved when:
- If n is odd, x = 3 gives the maximum sum.
- If n is even, x = 2 gives the maximum sum.

However, after analyzing edge cases (like n=3), we can see the pattern:
x = 3 if n == 3 else 2

This solution exploits this pattern.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    printf("%d\n", n == 3 ? 3 : 2);  // Output x based on the observed pattern
  }
}


// https://github.com/VaHiX/codeForces/