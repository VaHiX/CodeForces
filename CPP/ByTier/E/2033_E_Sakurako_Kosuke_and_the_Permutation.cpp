/*
 * Problem URL : https://codeforces.com/contest/2033/problem/E
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
#define ll long long
using namespace std;

int n, t, a[1000001];
bool b[1000001];

int dfs(int x) {
  if (b[x])
    return 0;
  b[x] = 1;
  return dfs(a[x]) + 1;
}

int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]);
    int ans = 0;
    for (int i = 1; i <= n; i++)
      if (!b[a[i]])
        ans += (dfs(a[i]) - 1) / 2;
    for (int i = 1; i <= n; i++)
      b[a[i]] = 0;
    printf("%d\n", ans);
  }
  return 0;
}
