/*
 * Problem URL : https://codeforces.com/problemset/problem/1785/A
 * Submit Date : 2025-08-21
 */

#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
int T, n, a[200005];
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]);
    sort(a + 1, a + n + 1);
    long long ans = 0ll;
    int tp = 0;
    for (int i = 1; i <= n; i++) {
      if (a[i] <= tp)
        continue;
      ans += (a[i] - tp - 1);
      tp++;
    }
    printf("%lld\n", ans);
  }
  return 0;
}