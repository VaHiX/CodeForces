/*
 * Problem URL : https://codeforces.com/problemset/problem/2055/F
 * Submit Date : 2025-08-24
 */

#include <stdio.h>
#include <string.h>

#define N 200000

int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }
int abs_(int a) { return a > 0 ? a : -a; }

void zzz(int *aa, int *zz, int n) {
  int i, l, r;

  memset(zz, 0, n * sizeof *zz);
  for (i = 1, l = 0, r = 0; i < n; i++)
    if (i + zz[i - l] < r)
      zz[i] = zz[i - l];
    else {
      l = i, r = max(r, i);
      while (r < n && aa[r] == aa[r - l])
        r++;
      zz[i] = r - l;
    }
}

int main() {
  int t;

  scanf("%d", &t);
  while (t--) {
    static int ll[N], rr[N], aa[N * 2], zzl[N], zzr[N], zz[N * 2], cc[N];
    int n, h, i, k, c, d, tmp, yes;
    long long area, sum;

    scanf("%d", &n);
    area = 0;
    for (i = 0; i < n; i++) {
      scanf("%d%d", &ll[i], &rr[i]);
      area += rr[i] - ll[i] + 1;
    }
    c = rr[0] - ll[0] + 1;
    yes = 1;
    if (c % 2 != 0)
      yes = 0;
    for (i = 0; i < n; i++)
      if (rr[i] - ll[i] + 1 != c || i > 0 && abs_(ll[i] - ll[i - 1]) >= c / 2) {
        yes = 0;
        break;
      }
    if (yes) {
      printf("YES\n");
      continue;
    }
    yes = 0;
    for (h = 0; h < 2; h++) {
      for (i = n - 1; i > 0; i--)
        aa[n - 1 - i] = ll[i] - ll[i - 1];
      zzz(aa, zzl, n - 1);
      for (i = 0; i + 1 < n; i++)
        aa[i] = rr[i + 1] - rr[i];
      zzz(aa, zzr, n - 1);
      for (i = 0; i + 1 < n; i++)
        aa[i] = ll[i + 1] - ll[i];
      for (i = 0; i + 1 < n; i++)
        aa[n - 1 + i] = rr[i + 1] - rr[i];
      zzz(aa, zz, (n - 1) * 2);
      sum = 0;
      for (k = 1; k < n; k++) {
        sum += rr[n - k] - ll[k - 1];
        if (k * 2 >= n &&
            sum + (long long)(c - (rr[n - k] - ll[0])) * k == area / 2) {
          d = rr[n - k] - rr[0];
          if (ll[n - 1] - ll[k - 1] != d ||
              (k == 1 ? 0 : zzl[n - k]) < n - k - 1)
            continue;
          if ((k + 1 == n ? 0 : zzr[n - k]) < n - k - 1)
            continue;
          if (k * 2 > n + 1 &&
              zz[(n - 1) * 2 - (k * 2 - n - 1)] < k * 2 - n - 1)
            continue;
          yes = 1;
          for (i = 0; i < n; i++) {
            cc[i] = rr[i] - ll[i] + 1;
            if (i >= n - k)
              cc[i] -= cc[i - (n - k)];
            if ((i < k ? cc[i] <= 0 : cc[i] != 0)) {
              yes = 0;
              break;
            }
          }
          for (i = 0; i + n - k < k; i++)
            if (ll[i + n - k] + cc[i + n - k] != ll[i] + d) {
              yes = 0;
              break;
            }
          for (i = 0; i + 1 < k; i++)
            if (max(ll[i], ll[i + 1]) >
                min(ll[i] + cc[i] - 1, ll[i + 1] + cc[i + 1] - 1)) {
              yes = 0;
              break;
            }
          if (yes)
            goto out;
        }
      }
      for (i = 0; i < n; i++)
        tmp = -ll[i], ll[i] = -rr[i], rr[i] = tmp;
    }
  out:
    printf(yes ? "YES\n" : "NO\n");
  }
  return 0;
}
