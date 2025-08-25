/*
 * Problem URL : https://codeforces.com/problemset/problem/1971/A
 * Submit Date : 2025-08-12
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    printf("%ld %ld\n", (x < y ? x : y), (x > y ? x : y));
  }
}
