/*
 * Problem URL : https://codeforces.com/problemset/problem/1004/C
 * Submit Date : 2025-08-20
 */

#include <bits/stdc++.h>
using namespace std;
const int maxn = 500005;
int n, m, T, tot;
long long res;
int a[maxn], ans[maxn], vis[maxn];
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    ans[a[i]] = tot;
    if (vis[a[i]] == 0)
      tot++;
    vis[a[i]] = 1;
  }
  for (int i = 1; i <= 100000; i++)
    res += ans[i];
  printf("%lld\n", res);
  return 0;
}
