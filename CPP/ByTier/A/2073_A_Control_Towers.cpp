/*
 * Problem URL : https://codeforces.com/contest/2073/problem/A
 * Submit Date : 2025-08-25
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
char s[2004][2004];
int n, m, r[2004], c[2004], w[2004];
ll ans;
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++)
    scanf("%s", s[i]);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (s[i][j] == '.')
        r[i]++, c[j]++;
  for (int i = 0; i < n; i++)
    ans += (ll)r[i] * (r[i] - 1) * (r[i] - 2) * (r[i] - 3);
  for (int i = 0; i < m; i++)
    ans += (ll)c[i] * (c[i] - 1) * (c[i] - 2) * (c[i] - 3);
  for (int i = 0; i < n; i++) {
    int t = 0;
    for (int j = 0; j < m; j++)
      if (s[i][j] == '.') {
        ans += 2ll * (r[i] - 1) * (c[j] - 1) * (r[i] + c[j] - 4);
        ans += 2ll * w[j] * (r[i] - 1), w[j] += r[i] - 1,
            ans += 2ll * t * (c[j] - 1), t += c[j] - 1;
      }
  }
  printf("%lld", ans);
}