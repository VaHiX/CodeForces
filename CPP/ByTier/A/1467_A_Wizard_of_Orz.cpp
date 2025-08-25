/*
 * Problem URL : https://codeforces.com/contest/1467/problem/A
 * Submit Date : 2025-08-24
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/1467/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    if (n >= 1) {
      printf("9");
    }
    if (n >= 2) {
      printf("8");
    }
    for (long p = 0; p + 2 < n; p++) {
      printf("%ld", (9 + p) % 10);
    }
    puts("");
  }
}
