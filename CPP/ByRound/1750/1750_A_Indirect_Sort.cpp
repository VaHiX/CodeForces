/*
 * Problem URL : https://codeforces.com/problemset/problem/1750/A
 * Submit Date : 2025-08-20
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long x;
    scanf("%ld", &x);
    bool possible = (x == 1);
    for (long p = 1; p < n; p++) {
      scanf("%ld", &x);
    }
    puts(possible ? "Yes" : "No");
  }
}
