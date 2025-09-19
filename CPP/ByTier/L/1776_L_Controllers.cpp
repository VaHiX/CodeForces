/*
 * Problem URL : https://codeforces.com/contest/1776/problem/L
 * Submit Date : 2025-09-08
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
char num[200010];
int main() {
  int n;
  scanf("%d%s", &n, num + 1);
  int t, f = 0;
  for (int i = 1; i <= n; i++)
    f += (num[i] == '+');
  scanf("%d", &t);
  f = min(f, n - f);
  while (t--) {
    int x, y;
    scanf("%d%d", &x, &y);
    if (x == y) {
      puts(2 * f == n ? "YES" : "NO");
      continue;
    }
    if (x > y)
      swap(x, y);
    ll mid = 1ll * x * (n - 2 * f);
    if (mid % (y - x) == 0 && mid / (y - x) <= f)
      puts("YES");
    else
      puts("NO");
  }
}