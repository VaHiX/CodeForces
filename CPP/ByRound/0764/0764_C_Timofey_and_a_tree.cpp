/*
 * Problem URL : https://codeforces.com/problemset/problem/764/C
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 2E5 + 10;
int a[N], b[N], c[N];
int mp[N];

int main() {
  int n, f = 0, ans = 0, sum = 0;
  cin >> n;
  for (int i = 1; i <= n - 1; i++)
    scanf("%d%d", &a[i], &b[i]);
  for (int i = 1; i <= n; i++)
    scanf("%d", &c[i]);
  for (int i = 1; i <= n - 1; i++)
    if (c[a[i]] != c[b[i]])
      sum++, mp[a[i]]++, mp[b[i]]++;
  for (int i = 1; i <= n; i++)
    if (mp[i] == sum) {
      ans = i;
      f = 1;
      break;
    }

  if (f)
    printf("YES\n%d\n", ans);
  else
    puts("NO");
  return 0;
}
