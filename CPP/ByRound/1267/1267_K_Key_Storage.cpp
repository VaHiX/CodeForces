/*
 * Problem URL : https://codeforces.com/contest/1267/problem/K
 * Submit Date : 2025-09-08
 */

#include <bits/stdc++.h>
#define int long long
using namespace std;
int i, j, k, T, x, s, p, c[23][23], f[23];
void solve() {
  for (i -= 2, j = 1; i >= 0; i--, j++) {
    if (!i)
      j--;
    s *= c[j][f[i]], j -= f[i];
  }
  return;
}
signed main() {
  scanf("%lld", &T);
  for (i = c[0][0] = 1; i < 21; i++)
    for (c[i][0] = j = 1; j <= i; j++)
      c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
  while (T--) {
    memset(f, 0, sizeof(f));
    scanf("%lld", &x);
    i = 2;
    s = 1;
    p = 0;
    while (x) {
      f[x % i]++;
      x /= i;
      i++;
    }
    k = i;
    for (i -= 2, j = 1; i >= 0; i--, j++) {
      if (!i)
        j--;
      s *= c[j][f[i]];
      j -= f[i];
    }
    i = k - 1;
    f[0]--;
    if (!f[k - 2])
      for (p = 1, i -= 2, j = 1; i >= 0; i--, j++) {
        if (!i)
          j--;
        p *= c[j][f[i]], j -= f[i];
      }
    printf("%lld\n", s - p - 1);
  }
  return 0;
}