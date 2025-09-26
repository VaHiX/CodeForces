/*
 * Problem URL : https://codeforces.com/contest/1355/problem/D
 * Submit Date : 2025-09-06
 */

#include <cstdio>

int main() {

  long n, s;
  scanf("%ld %ld", &n, &s);
  if (s < 2 * n) {
    puts("NO");
  } else {
    puts("YES");
    for (long p = 1; p < n; p++) {
      printf("2 ");
    }
    printf("%ld\n1\n", s - 2 * (n - 1));
  }

  return 0;
}
