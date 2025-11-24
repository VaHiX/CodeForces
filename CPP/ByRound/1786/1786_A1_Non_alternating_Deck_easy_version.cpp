// Problem: CF 1786 A1 - Non-alternating Deck (easy version)
// https://codeforces.com/contest/1786/problem/A1

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long rem(n), alice(0), bob(0);
    for (long p = 1; rem > 0 && p <= n; p++) {
      long take = (rem < p) ? rem : p;
      // Determine to whom to give the cards based on position p
      if (p % 4 <= 1) {
        alice += take;
      } else {
        bob += take;
      }
      rem -= take;
    }
    printf("%ld %ld\n", alice, bob);
  }
}


// https://github.com/VaHiX/codeForces/