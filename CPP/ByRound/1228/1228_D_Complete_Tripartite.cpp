/*
 * Problem URL : https://codeforces.com/contest/1228/problem/D
 * Submit Date : 2025-09-02
 */

#include <bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int MAXA = 2e5;
#define ULL long long
int n, m, x, y, N, col[MAXA];
ULL a[MAXA], f[MAXA];
map<ULL, int> ma;
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++)
    a[i] = rng();
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &x, &y);
    f[x] ^= a[y];
    f[y] ^= a[x];
  }
  for (int i = 1; i <= n; i++) {
    if (!f[i])
      return printf("-1"), 0;
    x = ma[f[i]];
    if (!x) {
      x = ++N;
      if (x > 3)
        return printf("-1"), 0;
      ma[f[i]] = x;
    }
    col[i] = x;
  }
  if (N < 3)
    return printf("-1"), 0;
  for (int i = 1; i <= n; i++)
    printf("%d ", col[i]);
}
