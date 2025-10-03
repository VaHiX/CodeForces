/*
 * Problem URL : https://codeforces.com/problemset/problem/1610/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    if (n == 1 && m == 1) {
      puts("0");
    } else if (n == 1 || m == 1) {
      puts("1");
    } else {
      puts("2");
    }
  }
}
