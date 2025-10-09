/*
 * Problem URL : https://codeforces.com/contest/1906/problem/K
 * Submit Date : 2025-09-07
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
const int N = 1 << 17;
const int MO = 998244353;
void ad(int &x, int y) {
  x += y;
  if (x >= MO)
    x -= MO;
}
int mul(int x, int y) { return (LL)x * y % MO; }
int w, n, m, a[N], c[N], d[N];
int main() {
  int i, j, x, s;
  scanf("%d", &w);
  for (i = 1; i <= w; i++)
    scanf("%d", &x), a[x]++;
  m = 17;
  n = 1 << m;
  for (j = 0; j < m; j++)
    for (i = 0; i < n; i++)
      if (i & (1 << j))
        ad(a[i ^ (1 << j)], a[i]);
  c[0] = 1;
  for (i = 1; i <= m; i++)
    c[i] = mul(c[i - 1], MO - 2);
  for (i = 0; i < n; i++)
    a[i] = mul(a[i], c[__builtin_popcount(i)]);
  for (j = 0; j < m; j++)
    for (i = 0; i < n; i++)
      if (i & (1 << j))
        ad(a[i], a[i ^ (1 << j)]);
  d[0] = 1;
  for (i = 1; i <= w; i++)
    d[i] = mul(d[i - 1], MO - 3);
  s = 0;
  for (i = 0; i < n; i++)
    ad(s, d[(w + a[i]) % MO / 2]);
  if (w % 2)
    s = mul(s, MO - 1);
  for (i = 0; i < m; i++)
    s = mul(s, (MO + 1) / 2);
  printf("%d\n", s);
  return 0;
}