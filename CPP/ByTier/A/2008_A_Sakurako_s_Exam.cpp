/*
 * Problem URL : https://codeforces.com/problemset/problem/2008/A
 * Submit Date : 2025-08-10
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    puts(((a % 2) || (b % 2 && a < 2)) ? "NO" : "YES");
  }
}
