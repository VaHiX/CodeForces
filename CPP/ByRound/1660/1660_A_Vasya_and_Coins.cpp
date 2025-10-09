/*
 * Problem URL : https://codeforces.com/problemset/problem/1660/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    printf("%ld\n", (a ? (a + 2 * b) : 0) + 1);
  }
}
