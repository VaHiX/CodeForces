/*
 * Problem URL : https://codeforces.com/contest/1369/problem/A
 * Submit Date : 2025-08-26
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    puts(n % 4 ? "NO" : "YES");
  }

  return 0;
}
