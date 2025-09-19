/*
 * Problem URL : https://codeforces.com/problemset/problem/2116/C
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 5000 + 5, mod = 998244353, INF = 5000 + 5;

int kase, n, a[N], f[N];

int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }

int main() {
  scanf("%d", &kase);
  while (kase--) {
    memset(f, 0x3f, sizeof(f));
    scanf("%d", &n);
    for (int i = 1, x; i <= n; i++) {
      scanf("%d", &a[i]);
      x = a[i];
      for (int j = 5000; j >= 1; j--)
        if (f[j] < INF) {
          int g = gcd(x, j);
          f[g] = min(f[g], f[j] + 1);
        }
      f[x] = 0;
    }
    int res = 0, ans = 0;
    for (int i = 1; i <= 5000; i++)
      if (f[i] < INF) {
        res = i;
        break;
      }
    if (f[res] == 0) {
      for (int i = 1; i <= n; i++)
        if (a[i] != res)
          ans++;
      printf("%d\n", ans);
    } else
      printf("%d\n", f[res] + n - 1);
  }
  return 0;
}