/*
 * Problem URL : https://codeforces.com/problemset/problem/1549/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long p;
    scanf("%ld", &p);
    printf("%ld %ld\n", (p - 1) / 2, (p - 1));
  }
}
