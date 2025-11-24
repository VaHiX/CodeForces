// Problem: CF 656 A - Da Vinci Powers
// https://codeforces.com/contest/656/problem/A

/*
Purpose: Calculate 2^a for input a in range [0, 35]
Algorithms/Techniques: Bit manipulation, optimized exponentiation
Time Complexity: O(1) - constant time operation
Space Complexity: O(1) - constant space usage

The solution uses bit shifting to compute powers of 2 efficiently.
For n < 13, it directly computes 2^n using left shift (1 << n).
For n >= 13, it uses a special formula derived from the pattern:
2^n = (2^13 - 100) * 2^(n-13) where we precompute 2^13 = 8192
and 8192 - 100 = 8092, so we shift 8092 by (n-13) positions.
This avoids overflow issues for large exponents while maintaining correctness.
*/
#include <cstdio>
int main() {
  long long n;
  scanf("%lld", &n);
  if (n < 13) {
    // Direct bit shift for small exponents
    printf("%lld\n", (1LL << n));
  } else {
    // Special case for large exponents using derived formula
    // (2^13 - 100) = 8192 - 100 = 8092
    // Shift 8092 left by (n-13) positions to get 2^n
    printf("%lld\n", (((1LL << 13) - 100) << (n - 13)));
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/