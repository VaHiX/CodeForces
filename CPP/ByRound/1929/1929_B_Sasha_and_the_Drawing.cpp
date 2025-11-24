// Problem: CF 1929 B - Sasha and the Drawing
// https://codeforces.com/contest/1929/problem/B

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    long ans(2 * n); // Initialize answer with maximum possible cells needed (2*n)
    if (k <= 4 * n - 4) { // If k is small enough to be covered by placing cells on diagonals optimally
      ans = (k + 1) / 2; // Each pair of diagonals can be covered by one cell, so ceil(k/2)
    } else if (k <= 4 * n - 3) { // If k is slightly larger, but still manageable
      ans = 2 * n - 1; // Some diagonals require more cells to cover optimally
    }
    printf("%ld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/