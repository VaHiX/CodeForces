// Problem: CF 2122 B - Pile Shuffling
// https://codeforces.com/contest/2122/problem/B

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long long total(0);
    for (long p = 0; p < n; p++) {
      long a, b, c, d;
      scanf("%ld %ld %ld %ld", &a, &b, &c, &d); // Read current and target states of pile
      if (b > d) {
        // If current ones > target ones, we need to move (b - d) ones from bottom
        // and also add 'a' operations for moving zeros to top if needed
        total += a + (b - d);
      } else {
        // If current ones <= target ones, calculate difference in zeros that must be moved
        // Only move zeros if they are more than required
        total += (a > c ? (a - c) : 0);
      }
    }
    printf("%lld\n", total);
  }
}

// https://github.com/VaHiX/codeForces/