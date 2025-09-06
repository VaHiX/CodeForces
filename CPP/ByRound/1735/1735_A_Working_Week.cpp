/*
 * Problem URL : https://codeforces.com/problemset/problem/1735/A
 * Submit Date : 2025-08-21
 */

#include <iostream>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    printf("%ld\n", (n - 6) / 3);
  }
}
