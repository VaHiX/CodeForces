/*
 * Problem URL : https://codeforces.com/problemset/problem/2080/D
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 4e5 + 10;
int n, a[N], t[N], ct, op[N], m[N], k[N], l[N], r[N], w[N];
struct bit {
  int c[N], sum;
  void add(int a, int x) {
    for (sum += x; a <= ct; a += (a & -a))
      c[a] += x;
  }
  int ask(int a) {
    if (a == ct)
      return sum;
    int b = 0;
    for (; a; a -= (a & -a))
      b += c[a];
    return b;
  }
  int find(int x) {
    int b = 0, i;
    for (i = 20; i >= 0; i--)
      if (b + (1 << i) <= ct && c[b + (1 << i)] <= x)
        b += (1 << i), x -= c[b];
    return b;
  }
} c1, c2;
void add(int a, int x) { c1.add(a, x), c2.add(a, t[a] * x); }
int s1, t1, s2, t2, s3, t3, s4, t4, o, M;

int get(int x) {
  int p = c1.find(x);
  return c2.ask(p) + t[p + 1] * (x - c1.ask(p));
}

int lb(int x) { return lower_bound(&t[1], &t[ct] + 1, x) - t; }

int presum(int x) {
  if (x <= s1)
    return get(x);
  if (x <= s1 + s2)
    return t1 + (o - 1) * (x - s1);
  if (x <= s1 + s2 + s3)
    return t1 + t2 + o * (x - s1 - s2);
  return t1 + t2 + t3 + get(x) - get(s1 + s2 + s3) - (x - s1 - s2 - s3) * M;
}

void slv(int m, int k, int l, int r) {
  int L = 0, R = n, mid, i;
  while (L < R) {
    mid = (L + R + 1) >> 1;
    int a = c1.find(n - mid);
    int b = get(n - mid);
    int p = lb(t[a + 1] - m) - 1;
    int s = c2.ask(p), u = c1.ask(p);
    if (mid * m + b - s - (t[a + 1] - m) * (n - mid - u) <= m * k)
      L = mid;
    else
      R = mid - 1;
  }
  s4 = L, t4 = c2.sum - get(n - L);
  L = -2e9, R = 1e9;
  if (s4)
    R = t[c1.find(n - s4) + 1] - m;
  while (L < R) {
    mid = (L + R) >> 1;
    int x = lb(mid) - 1;
    if ((c2.sum - t4 - c2.ask(x)) - mid * (n - s4 - c1.ask(x)) <= m * (k - s4))
      R = mid;
    else
      L = mid + 1;
  }
  int x = lb(L) - 1;
  int a = m * (k - s4) - ((c2.sum - t4 - c2.ask(x)) - L * (n - s4 - c1.ask(x)));
  s1 = c1.ask(x), t1 = c2.ask(x);
  s2 = a, t2 = (L - 1) * s2;
  s3 = n - s1 - s2 - s4, t3 = L * s3;
  o = L, M = m;
  if (l == -1) {
    for (i = 1; i <= n; i++)
      w[i] = presum(i);
    for (i = 1; i <= n; i++)
      printf("%lld%c", w[i] - w[i - 1], " \n"[i == n]);
  } else
    printf("%lld\n", presum(r) - presum(l - 1));
}

signed main() {
  int m0, k0, q, i;
  scanf("%lld%lld%lld%lld", &n, &m0, &k0, &q);
  for (i = 1; i <= n; i++)
    scanf("%lld", &a[i]), t[i] = a[i];
  ct = n;
  for (i = 1; i <= q; i++) {
    scanf("%lld%lld%lld", &op[i], &m[i], &k[i]);
    if (op[i] == 1)
      scanf("%lld", &l[i]), r[i] = l[i];
    if (op[i] == 2)
      t[++ct] = k[i];
    if (op[i] == 3)
      scanf("%lld%lld", &l[i], &r[i]);
  }
  sort(&t[1], &t[ct] + 1);
  ct = unique(&t[1], &t[ct] + 1) - t - 1;
  for (i = 1; i <= n; i++)
    a[i] = lb(a[i]), add(a[i], 1);
  slv(m0, k0, -1, -1);
  for (i = 1; i <= q; i++) {
    if (op[i] == 2)
      add(a[m[i]], -1), a[m[i]] = lb(k[i]), add(a[m[i]], 1);
    else
      slv(m[i], k[i], l[i], r[i]);
  }
  return 0;
}