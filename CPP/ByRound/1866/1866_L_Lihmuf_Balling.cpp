/*
 * Problem URL : https://codeforces.com/contest/1866/problem/L
 * Submit Date : 2025-09-07
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 2010;
int b[N];
int n, m;
int main() {
  scanf("%d%d", &n, &m);
  long long an = 0;
  int p = 1;
  for (int i = 2; i <= m; i++) {
    for (int j = 1; j <= i; j++)
      b[j] = 0;
    int x = i;
    int y = 1;
    long long s = 0;
    while (!b[x] && x <= n) {
      b[x] = 1;
      int t = (n - x) / i;
      int t1;
      if (y - x < 0)
        t1 = 0;
      else
        t1 = (y - x) / (i - 1) + 1;
      if (t1 <= t)
        s += 1ll * x * (t - t1 + 1) + 1ll * (t1 + t) * (t - t1 + 1) / 2 * i;
      x = x + (t + 1) * i - n;
      y += (t + 1);
    }
    if (an < s) {
      an = s;
      p = i;
    }
  }
  printf("%d\n", p);
}