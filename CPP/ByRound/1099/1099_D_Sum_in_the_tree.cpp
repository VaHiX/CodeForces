/*
 * Problem URL : https://codeforces.com/problemset/problem/1099/D
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, p[100005], s[100005], ans = 0, i;
int main() {
  scanf("%lld", &n);
  for (i = 2; i <= n; i++)
    scanf("%lld", &p[i]);
  for (i = 1; i <= n; i++)
    scanf("%lld", &s[i]);
  for (i = 1; i <= n; i++)
    if (s[i] == -1)
      s[i] = 1e9 + 1;
  for (i = 2; i <= n; i++)
    s[p[i]] = min(s[i], s[p[i]]);
  for (i = 1; i <= n; i++) {
    if (s[i] < s[p[i]]) {
      cout << -1 << endl;
      return 0;
    }
    if (s[i] <= 1e9)
      ans += s[i] - s[p[i]];
  }
  cout << ans << endl;
  return 0;
}