/*
 * Problem URL : https://codeforces.com/problemset/problem/1163/A
 * Submit Date : 2025-08-27
 */

#include <cstdio>

int main() {

  long n, m;
  scanf("%ld %ld", &n, &m);
  printf("%ld\n", (m < n - m) ? (m > 0 ? m : 1) : (n - m));

  return 0;
}
