// Problem: CF 1076 B - Divisor Subtraction
// https://codeforces.com/contest/1076/problem/B

#include <cstdio>
typedef long long ll;
int main() {
  ll n;
  scanf("%lld", &n);
  ll res(0);
  if (n % 2) { // If n is odd
    for (ll p = 3; p * p <= n; p += 2) { // Check odd divisors starting from 3
      if (n % p == 0) { // Found smallest odd prime divisor
        n -= p; // Subtract it from n
        res = 1; // One subtraction performed
        break;
      }
    }
    if (!res) { // If no odd divisor found, n is prime
      res = 1; // One subtraction performed
      n = 0; // Final subtraction makes n zero
    }
  }
  if (n > 0) { // If n is still positive
    res += n / 2; // Add remaining steps (each step subtracts 2 from even numbers)
  }
  printf("%lld\n", res);
  return 0;
}
/*
B. Divisor Subtraction
Algorithm: Greedily subtract the smallest prime divisor at each step.
Time Complexity: O(√n) - We check divisors up to √n for odd numbers.
Space Complexity: O(1) - Only using a constant amount of extra space.
*/

// https://github.com/VaHiX/codeForces/