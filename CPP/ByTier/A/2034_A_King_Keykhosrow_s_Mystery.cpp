/*
 * Problem URL : https://codeforces.com/problemset/problem/2034/A
 * Submit Date : 2025-08-10
 */

#include <cstdio>

long gcd(long a, long b) { return (b == 0) ? a : gcd(b, a % b); }

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    printf("%ld\n", (a * b) / gcd(a, b));
  }
}
