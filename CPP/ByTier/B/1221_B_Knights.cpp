/*
 * Problem URL : https://codeforces.com/contest/1221/problem/B
 * Submit Date : 2025-09-11
 */

#include <cstdio>
#include <vector>

int main() {

  long n;
  scanf("%ld", &n);
  for (long row = 0; row < n; row++) {
    for (long col = 0; col < n; col++) {
      putchar((row + col) % 2 ? 'W' : 'B');
    }
    puts("");
  }

  return 0;
}
