/*
 * Problem URL : https://codeforces.com/problemset/problem/1295/A
 * Submit Date : 2025-08-22
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/1295/A
 * Submit Date : 2025-08-22
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    if (n & 1) {
      printf("7");
      n -= 3;
    }
    for (long p = 0; p < (n / 2); p++) {
      printf("1");
    };
    puts("");
  }

  return 0;
}
