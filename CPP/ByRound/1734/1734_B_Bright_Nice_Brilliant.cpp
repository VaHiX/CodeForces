/*
 * Problem URL : https://codeforces.com/problemset/problem/1734/B
 * Submit Date : 2025-08-21
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    for (long row = 0; row < n; row++) {
      for (long col = 0; col <= row; col++) {
        printf("%d ", col == 0 || col == row);
      }
      puts("");
    }
  }
}
