// Problem: CF 2093 A - Ideal Generator
// https://codeforces.com/contest/2093/problem/A

#include <cstdio>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long k;
    scanf("%ld", &k);
    puts(k % 2 ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/