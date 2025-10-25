/*
 * Problem URL : https://codeforces.com/contest/1089/problem/L
 * Submit Date : 2025-09-08
 */

#include <algorithm>
#include <cstdio>
const int N = 1e5 + 5;
int t[N], b[N], a[N];
int main() {
  int n, k, x, c = 0;
  long long s = 0;
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &x);
    if (x > t[a[i]])
      std::swap(x, t[a[i]]);
    if (x)
      b[++c] = x;
  }
  std::nth_element(b + 1, b + c - n + k, b + 1 + c);
  for (int i = 1; i <= c - n + k; ++i)
    s += b[i];
  printf("%lld\n", s);
  return 0;
}