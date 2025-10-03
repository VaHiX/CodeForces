/*
 * Problem URL : https://codeforces.com/problemset/problem/1311/A
 * Submit Date : 2025-08-13
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    if (a == b) {
      puts("0");
    } else if ((b > a) && ((b - a) % 2 == 1)) {
      puts("1");
    } else if ((b > a) && ((b - a) % 2 == 0)) {
      puts("2");
    } else if ((a > b) && ((a - b) % 2 == 0)) {
      puts("1");
    } else if ((a > b) && ((a - b) % 2 == 1)) {
      puts("2");
    }
  }

  return 0;
}
