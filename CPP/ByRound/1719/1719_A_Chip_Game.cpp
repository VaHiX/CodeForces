/*
 * Problem URL : https://codeforces.com/problemset/problem/1719/A
 * Submit Date : 2025-08-21
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    puts(((n + m) % 2) ? "Burenka" : "Tonya");
  }
}
