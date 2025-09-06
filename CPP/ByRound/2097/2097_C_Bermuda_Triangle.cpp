/*
 * Problem URL : https://codeforces.com/problemset/problem/2097/C
 * Submit Date : 2025-08-20
 */

#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

i64 Gcd(i64 a, i64 b, i64 &x, i64 &y) {
  if (!b) {
    x = 1;
    y = 0;
    return a;
  }

  i64 g = Gcd(b, a % b, y, x);
  y -= (a / b) * x;

  return g;
}

void Solve() {
  i64 n, x, y, vx, vy;
  cin >> n >> x >> y >> vx >> vy;

  i64 d = x * vy - y * vx;
  if (d % n != 0) {
    cout << -1 << "\n";
    return;
  }

  i64 dh = d / n;
  i64 u, v, g = Gcd(vy, vx, u, v);
  if (dh % g) {
    cout << -1 << "\n";
    return;
  }

  i64 xx = u * (dh / g);
  i64 yy = -v * (dh / g);
  vx /= g;
  vy /= g;

  auto cdiv = [](i64 a, i64 b) { return a > 0 ? (a + b - 1) / b : a / b; };
  i64 w = max(cdiv(1 - xx, vx), cdiv(1 - yy, vy));
  xx += vx * w;
  yy += vy * w;

  cout << xx + yy - 2 + (xx + yy) / 2 + llabs(xx - yy) / 2 << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  while (t--) {
    Solve();
  }

  return 0;
}