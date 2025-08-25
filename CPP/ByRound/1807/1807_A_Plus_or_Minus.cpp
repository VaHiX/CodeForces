/*
 * Problem URL : https://codeforces.com/problemset/problem/1807/A
 * Submit Date : 2025-08-19
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c;
    scanf("%ld %ld %ld", &a, &b, &c);
    puts((a + b == c) ? "+" : "-");
  }
}
