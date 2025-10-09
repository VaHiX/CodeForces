/*
 * Problem URL : https://codeforces.com/contest/547/problem/A
 * Submit Date : 2025-09-05
 */

#include <bits/stdc++.h>
using namespace std;
long long m, h1, h2, a1, a2, x1, x2, y1, y2, t1 = -1, t2 = -1, p = -1, q = -1;
int main() {
  cin >> m >> h1 >> a1 >> x1 >> y1 >> h2 >> a2 >> x2 >> y2;
  for (int i = 1; i <= 2 * m; i++) {
    h1 = (h1 * x1 + y1) % m;
    h2 = (h2 * x2 + y2) % m;
    if (h1 == a1)
      if (p == -1)
        p = i;
      else if (t1 == -1)
        t1 = i - p;
    if (h2 == a2)
      if (q == -1)
        q = i;
      else if (t2 == -1)
        t2 = i - q;
  }
  if (p == -1 || q == -1)
    return cout << -1, 0;
  for (int i = 1; i <= 2 * m; i++) {
    if (p == q)
      return cout << p, 0;
    if (p < q)
      p += t1;
    else
      q += t2;
  }
  return cout << -1, 0;
}
