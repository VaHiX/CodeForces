// Problem: CF 1243 C - Tile Painting
// https://codeforces.com/contest/1243/problem/C

// C. Tile Painting
// Problem: Determine the maximum number of different colors that can be used to paint tiles 
// such that for any two tiles i and j where (j-i) is a divisor of n greater than 1, they must have the same color.
// Algorithm:
// - If n is prime, we can use n colors since no two tiles satisfy the constraint.
// - Otherwise, find the smallest prime factor p of n. The number of colors is p because
//   tiles at positions with same remainder when divided by p will have the same color.
// Time Complexity: O(sqrt(n))
// Space Complexity: O(1)

#include <cstdio>
typedef long long ll;

int main() {
  ll n;
  scanf("%lld", &n);
  ll x(-1), y(-1);
  // Loop through potential divisors up to sqrt(n)
  for (ll p = 2; p * p <= n; p++) {
    if (n % p) {  // Skip if p is not a divisor
      continue;
    }
    if (x < 0) {  // First smallest prime factor
      x = p;
    }
    // Check if current divisor p satisfies the condition for y
    if ((p % x) != 0 || ((n / p) % x) != 0) {
      y = p;
      break;
    }
  }
  ll res(n);
  if (x < 0) {  // n is prime
    res = n;
  } else if (y < 0) {  // Only one distinct prime factor
    res = x;
  } else {  // Two distinct prime factors, result is 1
    res = 1;
  }
  printf("%lld\n", res);
  return 0;
}


// https://github.com/VaHiX/codeForces/