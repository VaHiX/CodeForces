/*
 * Problem URL : https://codeforces.com/contest/1246/problem/A
 * Submit Date : 2025-09-02
 */

#include <bits/stdc++.h>
using namespace std;
int n, m;
int solve() {
  for (int i = 1; i <= 10000; ++i) {
    n -= m;
    if (__builtin_popcount(n) <= i && i <= n)
      return i;
  }
  return -1;
}
int main() {
  scanf("%d %d", &n, &m);
  printf("%d\n", solve());
}