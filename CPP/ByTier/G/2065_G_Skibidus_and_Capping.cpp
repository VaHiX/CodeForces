/*
 * Problem URL : https://codeforces.com/problemset/problem/2065/G
 * Submit Date : 2025-08-23
 */

#include <stdio.h>
#include <vector>
using namespace std;
typedef long long ll;

int n, a[200002], c[200002], t[200002], p[200002], q[200002], s[200002];

void solve() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]), t[i] = s[i] = 0;
  ll ans = 0;
  int tmp = 0;
  for (int i = 1; i <= n; i++) {
    if (c[a[i]] == 2) {
      ans += t[p[a[i]]] + t[q[a[i]]] + t[a[i]] + 1;
      s[p[a[i]]]++;
      s[q[a[i]]]++;
      if (q[a[i]] == p[a[i]])
        s[p[a[i]]]--, ans -= t[q[a[i]]];
    } else if (c[a[i]] == 0)
      ans += tmp - t[a[i]] + s[a[i]], tmp++;
    t[a[i]]++;
  }
  printf("%lld\n", ans);
}

int main() {
  for (int i = 2; i <= 200000; i++)
    if (!c[i])
      for (int j = i + i; j <= 200000; j += i)
        c[j] = 1;
  for (int i = 2; i <= 200000; i++)
    if (c[i] == 0)
      for (int j = 2; i * j <= 200000; j++)
        if (c[j] == 0) {
          c[i * j] = 2;
          p[i * j] = i;
          q[i * j] = j;
        }
  int t;
  scanf("%d", &t);
  while (t--)
    solve();
}