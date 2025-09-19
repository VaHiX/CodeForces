/*
 * Problem URL : https://codeforces.com/problemset/problem/2122/A
 * Submit Date : 2025-08-10
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    puts((n == 1 || m == 1 || (n == 2 && m == 2)) ? "NO" : "YES");
  }
}
