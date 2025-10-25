// Problem: CF 1350 A - Orac and Factors
// https://codeforces.com/contest/1350/problem/A

#include <cstdio>
typedef long long ll;
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    ll d(n); // Initialize d with n to handle case when n is prime
    for (ll p = 2; p * p <= n; p++) { // Loop to find the smallest divisor greater than 1
      if (n % p == 0) { // If p divides n
        d = p; // Set d to the smallest divisor found
        break; // Exit loop as we found the smallest divisor
      }
    }
    printf("%lld\n", n + d + 2 * (k - 1)); // Output final result using formula derived from observation
  }
  return 0;
}

// https://github.com/VaHiX/codeForces/