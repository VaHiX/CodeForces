/*
 * Problem URL : https://codeforces.com/contest/799/problem/A
 * Submit Date : 2025-09-01
 */



#include <cstdio>

int main() {

  int n, t, k, d;
  scanf("%d %d %d %d", &n, &t, &k, &d);
  puts((d < ((n - 1) / k) * t) ? "YES" : "NO");

  return 0;
}
