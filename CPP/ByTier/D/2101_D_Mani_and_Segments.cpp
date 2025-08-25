/*
 * Problem URL : https://codeforces.com/problemset/problem/2101/D
 * Submit Date : 2025-08-18
 */

#include <bits/stdc++.h>
#define ll long long
using namespace std;
int t, n, a[200005], f[200005], g[200005];
ll ans;
int main() {
  scanf("%d", &t);
  while (t--) {
    ans = 1;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]);
    int minp = 1, maxp = 1;
    for (int i = 1, j = 1; i <= n;) {
      while (j < n) {
        if (a[j + 1] > a[maxp])
          maxp = ++j;
        else if (a[j + 1] < a[minp])
          minp = ++j;
        else
          break;
      }
      while (i <= min(maxp, minp))
        f[i++] = j;
      if (maxp < minp)
        maxp = i;
      else
        minp = i;
    }
    minp = maxp = n;
    for (int i = n, j = n; i >= 1;) {
      while (j > 1) {
        if (a[j - 1] > a[maxp])
          maxp = --j;
        else if (a[j - 1] < a[minp])
          minp = --j;
        else
          break;
        ans += (f[i] - j + 1);
      }
      while (i >= max(maxp, minp))
        g[i--] = j;
      if (maxp > minp)
        maxp = i;
      else
        minp = i;
    }
    printf("%lld\n", ans);
  }
}