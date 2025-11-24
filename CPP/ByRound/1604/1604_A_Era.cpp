// Problem: CF 1604 A - Era
// https://codeforces.com/contest/1604/problem/A

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long res(0);
    for (long p = 1; p <= n; p++) {
      long x;
      scanf("%ld", &x);
      long diff = x - p;  // Calculate how much exceeds the position limit
      res = (res > diff) ? res : diff;  // Keep track of maximum excess
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/