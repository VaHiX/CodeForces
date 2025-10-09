/*
 * Problem URL : https://codeforces.com/contest/1039/problem/A
 * Submit Date : 2025-09-02
 */

#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int RLEN = 1 << 18 | 1;

inline char nc() {

  static char ibuf[RLEN], *ib, *ob;

  (ib == ob) && (ob = (ib = ibuf) + fread(ibuf, 1, RLEN, stdin));

  return (ib == ob) ? -1 : *ib++;
}

inline LL rd() {

  char ch = nc();
  LL i = 0, f = 1;

  while (!isdigit(ch)) {
    if (ch == '-')
      f = -1;
    ch = nc();
  }

  while (isdigit(ch)) {
    i = (i << 1) + (i << 3) + ch - '0';
    ch = nc();
  }

  return i * f;
}

const int N = 2e5 + 50;

int n, c[N], d[N];

LL t, a[N], x[N];

int main() {

  n = rd(), t = rd();

  for (int i = 1; i <= n; i++)
    a[i] = rd();

  for (int i = 1; i <= n; i++)
    if ((x[i] = rd()) < x[i - 1] || x[i] < i) {
      puts("No");
      return 0;
    }

  for (int i = 1; i <= n; i++)
    ++c[i], --c[x[i]], d[x[i]] = 1;
  d[n] = 0;

  for (int i = 1; i <= n; i++) {

    c[i] += c[i - 1];

    if (c[i] && d[i]) {
      puts("No");
      return 0;
    }

    if (c[i])
      x[i] = a[i + 1] + t;

    x[i] = max(x[i - 1] + 1, x[i]);

    x[i] = max(x[i], a[i] + t);

    if (d[i] && x[i] >= a[i + 1] + t) {
      puts("No");
      return 0;
    }
  }
  puts("Yes");

  for (int i = 1; i <= n; i++)
    printf("%I64d ", x[i]);
}