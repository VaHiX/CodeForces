// Problem: CF 1060 B - Maximum Sum of Digits
// https://codeforces.com/contest/1060/problem/B

/*
B. Maximum Sum of Digits
Algorithm: Greedy approach to maximize digit sum of two numbers that sum to n.
Approach:
- To maximize the sum of digits S(a) + S(b) where a + b = n, we want to distribute the digits
  such that both a and b have high digit sums.
- We try to make one of the numbers as close to a number consisting only of 9s (like 999...9)
  as possible while keeping it <= n.
- The key insight is we test a = n - 1, then n - 10^k + 1 for suitable k (to maximize digit sum).
Time Complexity: O(log n) - due to digit operations on numbers up to 10^12
Space Complexity: O(1) - only using constant extra space
*/

#include <cstdio>
int main() {
  long long n, m, a(1), b;
  scanf("%lld", &n);
  m = n;
  // Find the highest power of 10 less than or equal to n
  while (a <= m) {
    a *= 10;
  };
  a /= 10;
  a -= 1;  // This makes a = 999...9 with same number of digits as n
  b = n - a;  // b is the remaining part which will have lower digit sum but still maximizes total
  long s(0);
  // Calculate sum of digits of a
  while (a > 0) {
    s += (a % 10);
    a /= 10;
  }
  // Calculate sum of digits of b
  while (b > 0) {
    s += (b % 10);
    b /= 10;
  }
  printf("%ld\n", s);
  return 0;
}


// https://github.com/VaHiX/codeForces/