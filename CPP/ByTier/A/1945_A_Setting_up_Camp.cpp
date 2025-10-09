/*
 * Problem URL : https://codeforces.com/problemset/problem/1945/A
 * Submit Date : 2025-08-12
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c;
    scanf("%ld %ld %ld", &a, &b, &c);
    if ((b % 3) && ((b % 3) + c < 3)) {
      puts("-1");
      continue;
    }
    printf("%ld\n", a + (b + c + 2) / 3);
  }
}
