/*
 * Problem URL : https://codeforces.com/problemset/problem/2066/B
 * Submit Date : 2025-08-23
 */

#include <algorithm>
#include <stdio.h>
using namespace std;
const int p = 1e9 + 7;

int n, f[200002], c[200002];
bool s[200002];

void solve() {
  scanf("%d", &n);
  bool t = 0, ok = 1;
  int len = 0, tmp = 0;
  for (int i = 1, x; i <= n; i++) {
    scanf("%d", &x);
    if (x)
      f[++len] = x;
    else if (!t)
      f[++len] = x, t = 1;
  }
  for (int i = 1; i <= len; i++)
    c[i] = min(c[i - 1], f[i]);
  for (int i = len; i > 1; i--) {
    if (f[i] <= n)
      s[f[i]] = 1;
    while (s[tmp])
      tmp++;
    if (tmp > c[i - 1]) {
      ok = 0;
      break;
    }
  }
  printf("%d\n", len - !ok);
  for (int i = 1; i <= n; i++)
    if (f[i] <= n)
      s[f[i]] = 0;
}

int main() {
  c[0] = (1 << 30);
  int t;
  scanf("%d", &t);
  while (t--)
    solve();
}