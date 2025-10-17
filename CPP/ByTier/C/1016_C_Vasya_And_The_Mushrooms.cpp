/*
 * Problem URL : https://codeforces.com/problemset/problem/1016/C
 * Submit Date : 2025-08-13
 */

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int maxn = 3e5 + 10;

int n, a[2][maxn];
ll suf[maxn], sum[maxn],
    pre[maxn]; // suf:从i到最后再回到i的贡献，pre:i之前的绕着走

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[0][i]);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[1][i]);
  for (int i = n; i >= 1; i--)
    sum[i] = sum[i + 1] + a[0][i] + a[1][i];
  for (int i = n; i >= 1; i--) {
    suf[i] =
        suf[i + 2] - 2LL * sum[i + 2] + (2LL * (i - 1) * a[(i % 2) ^ 1][i]) +
        ((2LL * i - 1) * a[(i % 2) ^ 1][i + 1]) +
        ((2LL * n - 2LL) * a[i % 2][i + 1]) + ((2LL * n - 1LL) * a[i % 2][i]);
  }
  ll ans = 0;
  for (int i = 1; i <= n + 1; i++) {
    ans = max(ans, pre[i - 1] + suf[i]);
    pre[i] = pre[i - 1] + ((2LL * i - 2LL) * a[(i % 2) ^ 1][i] +
                           ((2LL * i - 1LL) * a[i % 2][i]));
  }
  printf("%lld\n", ans);
}