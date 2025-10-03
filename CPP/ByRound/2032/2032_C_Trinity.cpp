/*
 * Problem URL : https://codeforces.com/contest/2032/problem/C
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
using namespace std;
int t, n, a[200001], ans;
int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]);
    sort(a + 1, a + n + 1);
    ans = n - 1;
    for (int i = 1, j = 2; i <= n; i++)
      while (j <= n && a[i] + a[i + 1] > a[j]) {
        ans = min(ans, i - 1 + n - j);
        j++;
      }
    printf("%d\n", ans);
  }
  return 0;
}