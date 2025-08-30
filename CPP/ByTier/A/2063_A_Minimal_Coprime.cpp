/*
 * Problem URL : https://codeforces.com/problemset/problem/2063/A
 * Submit Date : 2025-08-10
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    printf("%ld\n", b - a + (a == b && a == 1));
  }
}
