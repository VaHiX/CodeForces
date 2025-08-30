/*
 * Problem URL : https://codeforces.com/contest/1312/problem/A
 * Submit Date : 2025-08-27
 */



#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long m, n;
    scanf("%ld %ld", &m, &n);
    puts((m % n == 0) ? "YES" : "NO");
  }

  return 0;
}
