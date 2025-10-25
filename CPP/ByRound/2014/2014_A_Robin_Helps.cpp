// Problem: CF 2014 A - Robin Helps
// https://codeforces.com/contest/2014/problem/A

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    long s(0), cnt(0);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x >= k) {
        s += x;  // Robin takes all gold from this person
      } else if (!x && s) {
        --s;     // Robin gives 1 gold to the poor
        ++cnt;   // Increment count of people helped
      }
    }
    printf("%ld\n", cnt);
  }
}

// https://github.com/VaHiX/codeForces/