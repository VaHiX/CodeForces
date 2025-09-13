/*
 * Problem URL : https://codeforces.com/contest/2042/problem/C
 * Submit Date : 2025-08-25
 */

#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 200010;
int t, n, c[N];
char a[N];
ll k;
int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d%lld%s", &n, &k, a + 1);
    c[n + 1] = 0;
    for (int i = n; i >= 2; i--)
      if (a[i] == '0')
        c[i] = c[i + 1] - 1;
      else
        c[i] = c[i + 1] + 1;
    sort(c + 2, c + n + 1);
    ll sum = 0;
    int ans = 1;
    for (int i = n; i >= 2; i--)
      if (sum < k)
        sum += c[i], ans++;
      else
        break;
    if (sum < k)
      puts("-1");
    else
      printf("%d\n", ans);
  }
}