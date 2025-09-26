/*
 * Problem URL : https://codeforces.com/problemset/problem/1850/A
 * Submit Date : 2025-08-18
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    bool ans = (a + b >= 10) || (b + c >= 10) || (c + a >= 10);
    puts(ans ? "YES" : "NO");
  }
}
