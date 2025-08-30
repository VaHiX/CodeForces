/*
 * Problem URL : https://codeforces.com/problemset/problem/2074/A
 * Submit Date : 2025-08-09
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long l, r, d, u;
    scanf("%ld %ld %ld %ld", &l, &r, &d, &u);
    puts((l == r && l == d && d == u) ? "Yes" : "No");
  }
}
