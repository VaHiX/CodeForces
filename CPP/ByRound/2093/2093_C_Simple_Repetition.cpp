// Problem: CF 2093 C - Simple Repetition
// https://codeforces.com/contest/2093/problem/C

/*
C. Simple Repetition
time limit per test1 second
memory limit per test256 megabytes

Pasha loves prime numbers! Once again, in his attempts to find a new way to generate prime numbers, he became interested in an algorithm he found on the internet:
To obtain a new number y, repeat k times the decimal representation of the number x (without leading zeros).
For example, for x=52 and k=3, we get y=525252, and for x=6 and k=7, we get y=6666666.

The algorithm checks if such a repeated number y is prime. This involves checking the primality of very large numbers (up to 10^9 * 7 digits). However, the key observation is:
- If k > 1 and x != 1, then y can be expressed as x * (10^(n*k) - 1)/(10^n - 1) for an appropriate n.
  This form implies that y is composite for most cases.
- Special case when x = 1: only possible prime value is 11 (when k = 2), since 11 is a known prime.

Algorithm:
1. If x == 1 and k == 2 → return "Yes" (only valid case)
2. If x != 1 and k > 1 → return "No"
3. Else, we check whether x itself is prime using trial division up to sqrt(x)

Time Complexity: O(√x * t) where t is number of test cases.
Space Complexity: O(1)

*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, k;
    scanf("%ld %ld", &x, &k);
    if (x == 1) {
      puts(k == 2 ? "Yes" : "No"); // Only 11 is prime in form of repeated '1'
      continue;
    } else if (k > 1) {
      puts("No"); // For k > 1, numbers formed are composite due to factorization
      continue;
    }
    bool ans(true);
    for (long p = 2; p * p <= x; p++) {
      if (x % p) {
        continue; // Not a divisor, continue checking
      }
      ans = false;
      break;
    }
    puts(ans ? "Yes" : "No"); // Output result of primality test for x
  }
}


// https://github.com/VaHiX/codeForces/