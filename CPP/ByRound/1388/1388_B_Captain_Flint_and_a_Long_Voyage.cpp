/*
 * Problem URL : https://codeforces.com/contest/1388/problem/B
 * Submit Date : 2025-09-11
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long g = (n + 3) / 4;
    for (long p = g; p < n; p++) {
      printf("9");
    }
    for (long p = 0; p < g; p++) {
      printf("8");
    }
    puts("");
  }

  return 0;
}
