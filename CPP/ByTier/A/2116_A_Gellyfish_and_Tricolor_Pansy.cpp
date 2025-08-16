/*
 * Problem URL : https://codeforces.com/problemset/problem/2116/A
 * Submit Date : 2025-08-08
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c, d;
    scanf("%ld %ld %ld %ld", &a, &b, &c, &d);
    long x = (a < c ? a : c);
    long y = (b < d ? b : d);
    puts(x >= y ? "Gellyfish" : "Flower");
  }
}
