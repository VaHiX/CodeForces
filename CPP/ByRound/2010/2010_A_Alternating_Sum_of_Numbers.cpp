// Problem: CF 2010 A - Alternating Sum of Numbers
// https://codeforces.com/contest/2010/problem/A

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long long s(0); // Initialize alternating sum
    for (long p = 0; p < n; p++) { // Iterate through each element
      long x;
      scanf("%ld", &x);
      s += (p % 2 ? -1 : 1) * x; // Add x with alternating sign (odd index = negative, even index = positive)
    }
    printf("%lld\n", s);
  }
}

// https://github.com/VaHiX/codeForces/