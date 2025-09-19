/*
 * Problem URL : https://codeforces.com/problemset/problem/1852/A
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int T, n, k, a[N], s[N];

int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; ++i)
      scanf("%d", &a[i]);
    long long nw = 1;
    for (int i = 1, j = 0; i <= k; ++i) {
      while (j < n && a[j + 1] - j <= nw)
        ++j;
      nw += j;
    }
    printf("%lld\n", nw);
  }
}