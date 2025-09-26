/*
 * Problem URL : https://codeforces.com/contest/457/problem/B
 * Submit Date : 2025-09-06
 */

#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

#define ll long long

const int N = 100000;
int a[N], b[N];

int max(int a, int b) { return a > b ? a : b; }
ll min(ll a, ll b) { return a < b ? a : b; }
int main() {
  int i, n, m, f, xa, xb;
  ll sa, sb, ua, ub, ra, rb, ans;
  xa = xb = 0;
  ua = ub = ra = rb = sa = sb = 0;
  scanf("%d%d", &n, &m);
  for (i = 0; i < n; i++)
    scanf("%d", &a[i]), sa += a[i], xa = max(xa, a[i]);
  for (i = 0; i < m; i++)
    scanf("%d", &b[i]), sb += b[i], xb = max(xb, b[i]);
  for (f = i = 0; i < n; i++) {
    if (a[i] < sb)
      ra += a[i];
    else
      ra += sb, f = 1;
  }
  if (!f)
    ra += sb - xa;
  for (f = i = 0; i < m; i++) {
    if (b[i] < sa)
      rb += b[i];
    else
      rb += sa, f = 1;
  }
  if (!f)
    rb += sa - xb;
  ans = min(ra, rb);
  printf("%lld\n", ans);
  return 0;
}
