/*
 * Problem URL : https://codeforces.com/contest/594/problem/A
 * Submit Date : 2025-09-04
 */

#include <bits/stdc++.h>
using namespace std;
int n, a[200010];
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  sort(a + 1, a + 1 + n);
  int ans = 1000000000;
  for (int i = 1; i <= n / 2; i++)
    ans = min(ans, a[n / 2 + i] - a[i]);
  printf("%d", ans);
  return 0;
}
