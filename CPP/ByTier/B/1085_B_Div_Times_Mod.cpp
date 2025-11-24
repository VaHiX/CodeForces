// Problem: CF 1085 B - Div Times Mod
// https://codeforces.com/contest/1085/problem/B

/*
B. Div Times Mod
Task: Solve equation (x div k) * (x mod k) = n for smallest positive x.
Algorithm: Iterate over all possible values of (x mod k) which must be a divisor of n.
          For each valid modulo value b, compute quotient q = n / b,
          then x = q * k + b. Among all such candidates, return the minimum.
Time Complexity: O(sqrt(n)) - due to iterating up to sqrt(n) divisors
Space Complexity: O(1) - only using a constant amount of extra space

Input:
  Two integers n and k (1 <= n <= 10^6, 2 <= k <= 1000)
Output:
  Smallest positive integer x such that (x div k) * (x mod k) = n
*/

#include <cstdio>
int main() {
  long n, k;
  scanf("%ld %ld", &n, &k);
  long x(0);
  for (long b = k - 1; b > 0; b--) {     // Iterate from k-1 down to 1 for possible mod values
    if (n % b) {                         // If b is not a divisor of n, skip it
      continue;
    }
    x = (n / b) * k + b;                 // Compute candidate x: quotient * k + remainder
    break;                               // Since we go from largest to smallest mod,
                                         // first valid x is the minimal one
  }
  printf("%ld\n", x);
  return 0;
}


// https://github.com/VaHiX/codeForces/