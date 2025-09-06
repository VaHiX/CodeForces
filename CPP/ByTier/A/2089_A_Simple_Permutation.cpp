/*
 * Problem URL : https://codeforces.com/problemset/problem/2089/A
 * Submit Date : 2025-08-20
 */

#include <stdio.h>
#pragma GCC optimize("O3,unroll-loops")
const int N = 6e5;
char t[6], bf[N];
int main() {
  int T, po = 0;
  scanf("%d", &T);
  auto pm = [&](int n) {
    if (n < 2)
      return 0;
    for (int d = 2; d * d <= n; d++)
      if (n % d == 0)
        return 0;
    return 1;
  };
  auto wt = [&](int x) {
    int tp = 0;
    while (x) {
      t[tp++] = '0' + (x % 10);
      x /= 10;
    }
    while (tp--)
      bf[po++] = t[tp];
    bf[po++] = ' ';
  };
  while (T--) {
    int n;
    scanf("%d", &n);
    int p = n / 2;
    while (!pm(p))
      p++;
    int c = 0, R = p, L = p - 1;
    while (c < n) {
      if (R <= n && c++ < n)
        wt(R++);
      if (L > 0 && c++ < n)
        wt(L--);
    }
    bf[po - 1] = '\n';
    fwrite(bf, 1, po, stdout);
    po = 0;
  }
}