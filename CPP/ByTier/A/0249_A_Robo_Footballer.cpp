/*
 * Problem URL : https://codeforces.com/contest/249/problem/A
 * Submit Date : 2025-09-06
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

bool check(ld x1, ld y1, ld x2, ld y2, ld x, ld y, ll r) {
  ld a = y2 - y1, b = x1 - x2, c = y1 * x2 - y2 * x1;
  ld dist = abs(x * a + y * b + c) / sqrt(a * a + b * b);
  if (dist >= r)
    return true;
  else
    return false;
}
signed main() {
  ld y1, y2, yw, yb, xb;
  ll r;
  cin >> y1 >> y2 >> yw >> xb >> yb >> r;
  yw -= r;
  ld ya = r + y1, a = yw - ya, b = yw - yb;
  if (check(0, ya, xb * a / (a + b), yw, 0, y2, r))
    cout << setprecision(20) << fixed << xb * a / (a + b) << '\n';
  else
    cout << -1 << '\n';
}