/*
 * Problem URL : https://codeforces.com/problemset/problem/1245/A
 * Submit Date : 2025-08-18
 */

#include <cstdio>

long gcd(long a, long b) { return (b == 0) ? a : gcd(b, a % b); }

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    puts(gcd(a, b) <= 1 ? "Finite" : "Infinite");
  }

  return 0;
}
