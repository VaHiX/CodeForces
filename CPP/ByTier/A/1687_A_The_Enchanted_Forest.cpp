/*
 * Problem URL : https://codeforces.com/contest/1687/problem/A
 * Submit Date : 2025-08-31
 */

#include <bits/stdc++.h>
using namespace std;
long long i, n, k, s, T, a[200200];
int main() {
  scanf("%lld", &T);
  while (T--) {
    scanf("%lld %lld", &n, &k);
    s = 0;
    for (i = 1; i <= n; i++)
      scanf("%lld", &a[i]), a[i] += a[i - 1];
    if (n <= k)
      s = a[n] + n * (n - 1) / 2 + (k - n) * n;
    else
      for (i = k; i <= n; i++)
        s = max(s, a[i] - a[i - k] + k * (k - 1) / 2);
    printf("%lld\n", s);
  }
  return 0;
}