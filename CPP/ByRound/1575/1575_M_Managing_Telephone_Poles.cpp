/*
 * Problem URL : https://codeforces.com/contest/1575/problem/M
 * Submit Date : 2025-09-08
 */

#include <bits/stdc++.h>
using namespace std;
int n, m, x[2005][2005], c[2005], p[2005], q[2005], b[2005];
char s[2005];
long long ans;
int main() {
  cin >> n >> m;
  for (int i = 0; i <= n; i++) {
    scanf("%s", s);
    for (int j = 0; j <= m; j++)
      if (s[j] == '1')
        x[j][c[j]++] = i;
  }
  for (int i = 0; i <= n; i++) {
    int h = 0, t = -1;
    for (int j = 0; j <= m; j++)
      if (c[j]) {
        while (p[j] < c[j] - 1 &&
               abs(x[j][p[j]] - i) >= abs(x[j][p[j] + 1] - i))
          p[j]++;
        b[j] = (x[j][p[j]] - i) * (x[j][p[j]] - i) + j * j;
        while (h < t && 1ll * (b[j] - b[q[t]]) * (q[t] - q[t - 1]) <=
                            1ll * (b[q[t]] - b[q[t - 1]]) * (j - q[t]))
          t--;
        q[++t] = j;
      }
    for (int j = 0; j <= m; j++) {
      while (h < t &&
             -2 * q[h] * j + b[q[h]] >= -2 * q[h + 1] * j + b[q[h + 1]])
        h++;
      ans += -2 * q[h] * j + b[q[h]] + j * j;
    }
  }
  cout << ans;
}