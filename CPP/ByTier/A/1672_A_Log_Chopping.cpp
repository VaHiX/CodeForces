/*
 * Problem URL : https://codeforces.com/problemset/problem/1672/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long s(0);
    while (n--) {
      long x;
      scanf("%ld", &x);
      s += x - 1;
    }
    puts(s % 2 ? "errorgorn" : "maomao90");
  }
}
