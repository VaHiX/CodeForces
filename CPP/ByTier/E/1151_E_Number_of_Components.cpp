/*
 * Problem URL : https://codeforces.com/problemset/problem/1151/E
 * Submit Date : 2025-08-13
 */

#include <bits/stdc++.h>
using namespace std;
int n, a[100010];
long long ans;
int main() {
  scanf("%d", &n);

  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    ans += 1ll * a[i] * (n - a[i] + 1);
  }

  for (int i = 1; i < n; i++) {
    ans -= 1ll * min(a[i], a[i + 1]) * (n - max(a[i], a[i + 1]) + 1);
  }

  printf("%lld\n", ans);
  return 0;
}