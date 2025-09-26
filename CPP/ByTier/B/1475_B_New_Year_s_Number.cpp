/*
 * Problem URL : https://codeforces.com/contest/1475/problem/B
 * Submit Date : 2025-09-10
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    const long A = 2020;
    long n;
    scanf("%ld", &n);
    long x = n / A;
    long y = n % A;
    puts(x >= y ? "YES" : "NO");
  }
}
