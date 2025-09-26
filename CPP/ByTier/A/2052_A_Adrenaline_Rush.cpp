/*
 * Problem URL : https://codeforces.com/problemset/problem/2052/A
 * Submit Date : 2025-08-20
 */

#include <bits/stdc++.h>
using namespace std;
int n, m, T, x, y, a[10101], ans, vis[10101], b[10101];
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]), vis[a[i]] = i, b[i] = i;
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      if (a[i] > a[j])
        ans++;
      else
        ans += 2;
    }
  }
  printf("%d\n", ans);
  for (int i = n; i >= 1; i--) {
    int k = b[n];
    for (int j = n - 1; j >= n - i + 1; j--)
      printf("%d %d\n", k, b[j]), b[j + 1] = b[j];
    b[n - i + 1] = i;
    int j = n - i + 1;
    while (1) {
      if (j <= 1 || vis[b[j - 1]] < vis[b[j]])
        break;
      printf("%d %d\n", b[j], b[j - 1]);
      swap(b[j - 1], b[j]);
      j--;
    }
  }
  return 0;
}