/*
 * Problem URL : https://codeforces.com/problemset/problem/1761/A
 * Submit Date : 2025-08-20
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, a, b;
    scanf("%ld %ld %ld", &n, &a, &b);
    bool res = (a == n && b == n) || (a + b + 1 < n);
    puts(res ? "Yes" : "No");
  }
}
