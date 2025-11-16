// Problem: CF 1150 A - Stock Arbitraging
// https://codeforces.com/contest/1150/problem/A

#include <cstdio>

int main() {
  long n, m, r;
  scanf("%ld %ld %ld", &n, &m, &r);
  long bp(1e9); // buy price: minimum buying price among all opportunities
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    bp = (bp < x) ? bp : x; // track the lowest buy price
  }
  long ap(-1); // sell price: maximum selling price among all opportunities
  for (long p = 0; p < m; p++) {
    long x;
    scanf("%ld", &x);
    ap = (ap > x) ? ap : x; // track the highest sell price
  }
  long res = r + (ap > bp) * (ap - bp) * (r / bp); // calculate profit
  printf("%ld\n", res);
  return 0;
}


// https://github.com/VaHiX/codeForces/