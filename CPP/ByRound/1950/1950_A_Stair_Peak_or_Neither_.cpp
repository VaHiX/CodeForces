/*
 * Problem URL : https://codeforces.com/problemset/problem/1950/A
 * Submit Date : 2025-08-12
 */

#include <cstdio>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c;
    scanf("%ld %ld %ld", &a, &b, &c);
    if (a < b && b < c) {
      puts("STAIR");
    } else if (a < b && b > c) {
      puts("PEAK");
    } else {
      puts("NONE");
    }
  }
}
