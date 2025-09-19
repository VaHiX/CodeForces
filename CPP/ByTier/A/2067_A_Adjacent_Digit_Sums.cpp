/*
 * Problem URL : https://codeforces.com/problemset/problem/2067/A
 * Submit Date : 2025-08-09
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    puts((y == x + 1) || ((x > y) && !((x - y + 1) % 9)) ? "Yes" : "No");
  }
}
