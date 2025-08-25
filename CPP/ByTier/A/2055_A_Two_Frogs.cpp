/*
 * Problem URL : https://codeforces.com/problemset/problem/2055/A
 * Submit Date : 2025-08-10
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, a, b;
    scanf("%ld %ld %ld", &n, &a, &b);
    puts((a - b) % 2 ? "NO" : "YES");
  }
}
