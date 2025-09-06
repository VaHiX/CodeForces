/*
 * Problem URL : https://codeforces.com/contest/1326/problem/A
 * Submit Date : 2025-08-26
 */



#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    if (n <= 1) {
      puts("-1");
    } else {
      printf("2");
      for (long p = 1; p < n; p++) {
        printf("3");
      };
      puts("");
    }
  }

  return 0;
}
