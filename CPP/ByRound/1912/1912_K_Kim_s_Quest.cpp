/*
 * Problem URL : https://codeforces.com/contest/1912/problem/K
 * Submit Date : 2025-09-07
 */

#include <bits/stdc++.h>
#define mod (998244353)
using namespace std;
int n, a[200005];
long long cnt[2][2], f[2], cnt1[2];
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    a[i] %= 2;
  }
  cnt1[a[1]]++;
  for (int i = 2; i <= n; i++) {
    f[0] = f[1] = 0;
    if (a[i] == 1) {
      f[0] += cnt[1][0];
      f[1] += cnt[0][1];
    }
    if (a[i] == 0) {
      f[0] += cnt[0][0];
      f[1] += cnt[1][1];
    }
    cnt[0][a[i]] += f[0];
    cnt[1][a[i]] += f[1];
    cnt[1][a[i]] += cnt1[1];
    cnt[0][a[i]] += cnt1[0];
    cnt[0][a[i]] %= mod;
    cnt[1][a[i]] %= mod;
    cnt1[a[i]]++;
  }
  printf("%lld", (cnt[0][0] + cnt[0][1] + cnt[1][0] + cnt[1][1] + mod -
                  ((long long)(n - 1) * n / 2) % mod) %
                     mod);
  return 0;
}