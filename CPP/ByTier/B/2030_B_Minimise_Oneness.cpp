/*
 * Problem URL : https://codeforces.com/problemset/problem/2030/B
 * Submit Date : 2025-08-10
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    printf("1");
    for (long p = 1; p < n; p++) {
      printf("0");
    }
    puts("");
  }
}
