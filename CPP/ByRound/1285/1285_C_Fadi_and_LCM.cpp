// Problem: CF 1285 C - Fadi and LCM
// https://codeforces.com/contest/1285/problem/C

/*
C. Fadi and LCM
Purpose: Find two positive integers a and b such that LCM(a, b) = X and max(a, b) is minimized.
Approach: 
- Iterate through all possible divisors p of X up to sqrt(X)
- For each divisor p, check if gcd(p, X/p) = 1 (i.e., p and X/p are coprime)
- If they are coprime, then LCM(p, X/p) = X and max(p, X/p) is minimized
- Return the first such pair found (since we iterate from small to large)

Time Complexity: O(sqrt(X))
Space Complexity: O(1)

Input: Integer X (1 <= X <= 10^12)
Output: Two positive integers a and b such that LCM(a, b) = X and max(a, b) is minimized
*/
#include <cstdio>
typedef long long ll;
ll gcd(ll a, ll b) { return (b == 0) ? a : gcd(b, a % b); }
int main() {
  ll x;
  scanf("%lld", &x);
  ll a(0), b(0);
  for (ll p = 1; p * p <= x; p++) {
    if (x % p) {            // Skip if p is not a divisor of x
      continue;
    }
    if (gcd(p, x / p) > 1) { // Skip if p and x/p are not coprime
      continue;
    }
    a = p;                  // Found a valid pair
    b = x / p;
  }
  printf("%lld %lld\n", a, b);
  return 0;
}


// https://github.com/VaHiX/codeForces/