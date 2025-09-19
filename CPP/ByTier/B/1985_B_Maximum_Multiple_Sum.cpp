/*
 * Problem URL : https://codeforces.com/problemset/problem/1985/B
 * Submit Date : 2025-08-12
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    printf("%d\n", n == 3 ? 3 : 2);
  }
}
