// Problem: CF 1511 A - Review Site
// https://codeforces.com/contest/1511/problem/A

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long cnt(0);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      // For each reviewer, if they are not type 2 (downvote), increment upvote count
      cnt += (x != 2);
    }
    printf("%ld\n", cnt);
  }
}

// https://github.com/VaHiX/codeForces/