// Problem: CF 1328 A - Divisibility Problem
// https://codeforces.com/contest/1328/problem/A

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    long mod = (a % b);           // Calculate remainder when a is divided by b
    long ans = (mod > 0) ? (b - mod) : 0;  // If remainder is 0, no moves needed; otherwise, moves = b - remainder
    printf("%ld\n", ans);
  }
  return 0;
}

// https://github.com/VaHiX/codeForces/