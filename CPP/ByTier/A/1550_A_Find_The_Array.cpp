/*
 * Problem URL : https://codeforces.com/problemset/problem/1550/A
 * Submit Date : 2025-08-23
 */

#include <cmath>
#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long s;
    scanf("%ld", &s);
    long n = sqrt(s);
    while (n * n < s) {
      ++n;
    }
    printf("%ld\n", n);
  }
}
