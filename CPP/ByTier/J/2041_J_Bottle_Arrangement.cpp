/*
 * Problem URL : https://codeforces.com/contest/2041/problem/J
 * Submit Date : 2025-08-25
 */

#include <bits/stdc++.h>
#define M 500010
using namespace std;
int n, a[M], b[M], l[M], r[M], s[M], k, d;
int pd(int p, int x, int y) {
  if (x > y)
    return 0;
  int d = 1e6;
  if (b[n - p + x] <= a[p])
    d = min(d, pd(l[p], x, p - 1) + (b[n - p + x] == a[p]));
  if (b[n - y + p] <= a[p])
    d = min(d, pd(r[p], p + 1, y) + (b[n - y + p] == a[p]));
  return d;
}
int main() {
  std::ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> n;
  for (register int i = 1; i <= n; i++) {
    cin >> a[i];
    d = 0;
    while (k && a[s[k]] >= a[i]) {
      d = s[k];
      --k;
    }
    if (k)
      r[s[k]] = i;
    l[i] = d, s[++k] = i;
  }
  for (register int i = 1; i <= n; i++)
    cin >> b[i];
  sort(b + 1, b + n + 1);
  d = pd(s[1], 1, n);
  cout << (d == 1e6 ? -1 : d);
  return 0;
}