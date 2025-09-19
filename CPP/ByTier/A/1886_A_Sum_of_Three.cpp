/*
 * Problem URL : https://codeforces.com/problemset/problem/1886/A
 * Submit Date : 2025-08-15
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    if (n % 3 == 0) {
      if (n < 12) {
        puts("NO");
      } else {
        printf("YES\n1 4 %ld\n", n - 5);
      }
    } else {
      if (n < 7) {
        puts("NO");
      } else {
        printf("YES\n1 2 %ld\n", n - 3);
      }
    }
  }
}
