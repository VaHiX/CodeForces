/*
 * Problem URL : https://codeforces.com/problemset/problem/2053/I2
 * Submit Date : 2025-08-24
 */

#include <stdio.h>

#define N 3000000
#define MD 998244353

long long min(long long a, long long b) { return a < b ? a : b; }
long long max(long long a, long long b) { return a > b ? a : b; }

int main() {
  int t;

  scanf("%d", &t);
  while (t--) {
    static long long aa[N + 1], aamn[N + 1], aamx[N + 1];
    static int dp[N + 1], dp_[N + 1], dpmn[N + 1], dpmx[N + 1];
    int n, i, imn, imx, j, l, m, r, ans;
    long long d, amn, amx;

    scanf("%d", &n);
    for (l = 1; l <= n; l++)
      scanf("%lld", &aa[l]), aa[l] += aa[l - 1];
    d = aa[n];
    i = 0;
    while (i <= n && aa[i] >= 0 && aa[i] <= d)
      i++;
    if (i > n) {
      printf("1\n");
      continue;
    }
    l = 0, m = i;
    for (i = l; i < m; i++)
      dp[i] = 1;
    ans = 0;
    while (1) {
      r = m - 1, amn = aa[m - 1], amx = aa[m - 1];
      while (r <= n && amx - amn <= d) {
        if (++r > n)
          break;
        amn = min(amn, aa[r]), amx = max(amx, aa[r]);
      }
      if (r > n && amn >= 0 && amx <= d) {
        for (i = m - 1; i >= l; i--) {
          if (aa[i] < 0 || aa[i] > d)
            break;
          ans = (ans + dp[i]) % MD;
        }
        break;
      }
      amn = aa[m - 1], amx = aa[m - 1];
      for (i = m - 1; i >= l; i--) {
        amn = min(amn, aa[i]), amx = max(amx, aa[i]);
        aamn[i] = amn, aamx[i] = amx;
      }
      amn = aa[m], amx = aa[m];
      for (j = m; j < r; j++) {
        amn = min(amn, aa[j]), amx = max(amx, aa[j]);
        aamn[j] = amn, aamx[j] = amx;
      }
      dp_[m] = dpmn[m] = dpmx[m] = 0;
      for (i = m - 1; i >= l; i--) {
        dp_[i] = (dp_[i + 1] + dp[i]) % MD;
        dpmn[i] = (dpmn[i + 1] + dp[i] * (aamn[i] % MD)) % MD;
        dpmx[i] = (dpmx[i + 1] + dp[i] * (aamx[i] % MD)) % MD;
      }
      for (i = l, imn = m, imx = m, j = m; j < r; j++) {
        while (i < m && max(aamx[i], aamx[j]) - min(aamn[i], aamn[j]) > d)
          i++;
        imn = max(imn, i);
        while (imn > i && aamn[imn - 1] > aamn[j])
          imn--;
        imx = max(imx, i);
        while (imx > i && aamx[imx - 1] < aamx[j])
          imx--;
        dp[j] = dp_[i] * ((d + 1) % MD) % MD;
        dp[j] = (dp[j] + dp_[imn] * (aamn[j] % MD)) % MD;
        dp[j] = (dp[j] + ((long long)dpmn[i] - dpmn[imn])) % MD;
        dp[j] = (dp[j] - dp_[imx] * (aamx[j] % MD)) % MD;
        dp[j] = (dp[j] - ((long long)dpmx[i] - dpmx[imx])) % MD;
      }
      l = m, m = r;
    }
    if (ans < 0)
      ans += MD;
    printf("%d\n", ans);
  }
  return 0;
}
