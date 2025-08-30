/*
 * Problem URL : https://codeforces.com/problemset/problem/2029/A
 * Submit Date : 2025-08-10
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long l, r, k;
    scanf("%ld %ld %ld", &l, &r, &k);
    long res = (r / k) - l + 1;
    printf("%ld\n", res > 0 ? res : 0);
  }
}
