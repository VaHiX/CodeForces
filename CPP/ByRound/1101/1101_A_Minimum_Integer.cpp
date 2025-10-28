// Problem: CF 1101 A - Minimum Integer
// https://codeforces.com/contest/1101/problem/A

#include <cstdio>
int main() {
  long q;
  scanf("%ld", &q);
  while (q--) {
    long l, r, d;
    scanf("%ld %ld %ld", &l, &r, &d);
    long ans = d;
    if (l <= d && d <= r) {           // If d is within the range [l, r]
      ans = d * (1 + (r / d));         // Find next multiple of d after r
    }
    printf("%ld\n", ans);
  }
  return 0;
}

// https://github.com/VaHiX/codeForces/