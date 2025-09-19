/*
 * Problem URL : https://codeforces.com/problemset/problem/1260/B
 * Submit Date : 2025-08-19
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    bool ans = ((a + b) % 3) || (a > 2 * b) || (b > 2 * a);
    puts(ans ? "NO" : "YES");
  }

  return 0;
}
