/*
 * Problem URL : https://codeforces.com/contest/1710/problem/A
 * Submit Date : 2025-08-31
 */

#include <bits/stdc++.h>
const int K = 1e5 + 3;
int n, m, k, a[K];
bool Solve(int n, int m) {
  bool fl = 0;
  long long mx = 0;
  for (int i = 1; i <= k; i++)
    if (a[i] / m >= 2)
      mx += a[i] / m, fl |= a[i] / m >= 3;
  return (~n & 1 || fl) && mx >= n;
}
int main() {
  int T;
  scanf("%d", &T);
  for (; T--;) {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= k; i++)
      scanf("%d", a + i);
    puts(Solve(n, m) || Solve(m, n) ? "Yes" : "No");
  }
  return 0;
}