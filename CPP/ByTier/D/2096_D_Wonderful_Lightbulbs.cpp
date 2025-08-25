/*
 * Problem URL : https://codeforces.com/problemset/problem/2096/D
 * Submit Date : 2025-08-20
 */

#include <bits/stdc++.h>

void solve() {
  int n;
  scanf("%i", &n);
  int a = 0, b = 0;
  for (int x, y, i = 0; i < n; ++i) {
    scanf("%i%i", &x, &y);
    a ^= x;
    b ^= (x + y);
  }
  printf("%i %i\n", a, b - a);
}

int main() {
  int t;
  scanf("%i", &t);
  while (t--)
    solve();
  return 0;
}