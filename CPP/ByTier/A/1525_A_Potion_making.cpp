// Problem: CF 1525 A - Potion-making
// https://codeforces.com/contest/1525/problem/A

#include <cstdio>
long gcd(long a, long b) { return (b == 0) ? a : gcd(b, a % b); }
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long k;
    scanf("%ld", &k);
    long g = gcd(k, 100 - k); // Compute GCD of k and (100-k) to reduce the fraction
    long ans = k / g + (100 - k) / g; // Sum of reduced numerator and denominator gives minimum steps
    printf("%ld\n", ans);
  }
}

// https://github.com/VaHiX/codeForces/