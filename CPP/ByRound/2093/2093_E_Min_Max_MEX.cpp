/*
 * Problem URL : https://codeforces.com/problemset/problem/2093/E
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
using namespace std;
int T, n, k, a[200005], t[200005];
bool check(int mid) {
  int cnt = 0, ans = 0;
  for (int i = 0; i <= mid; i++)
    t[i] = 0;
  for (int i = 1; i <= n; i++) {
    if (a[i] < mid && t[a[i]] <= ans) {
      cnt++;
      t[a[i]] = ans + 1;
    }
    if (cnt == mid) {
      cnt = 0;
      ans++;
    }
  }
  return ans >= k;
}
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &k);

    for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]);
    int l = 0, r = n + 1;
    while (l < r) {
      int mid = (l + r + 1) / 2;
      if (check(mid))
        l = mid;
      else
        r = mid - 1;
    }
    printf("%d\n", l);
  }
  return 0;
}