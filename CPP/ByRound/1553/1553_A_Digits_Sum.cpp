/*
 * Problem URL : https://codeforces.com/problemset/problem/1553/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    printf("%ld\n", (n + 1) / 10);
  }
}
