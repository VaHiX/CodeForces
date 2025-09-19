/*
 * Problem URL : https://codeforces.com/contest/2073/problem/M
 * Submit Date : 2025-08-25
 */

#include <bits/stdc++.h>
#include <iostream>
#include <set>
using namespace std;
typedef long long ll;
const int maxn = 200111;
#define FF first
#define SS second
#define PB push_back
#define MP make_pair

struct point {
  ll x, y;
  point(ll X = 0, ll Y = 0) : x(X), y(Y) {}
  point operator+(const point &t) const { return point(x + t.x, y + t.y); }
  point operator-(const point &t) const { return point(x - t.x, y - t.y); }
  point operator*(const ll &t) const { return point(x * t, y * t); }
  point operator/(const ll &t) const { return point(x / t, y / t); }
  ll det(const point &t) const { return x * t.y - y * t.x; }
  double detd(const point &t) const { return 1.0 * x * t.y - 1.0 * y * t.x; }
  ll len2() const { return x * x + y * y; }
  void in() { scanf("%lld%lld", &x, &y); }
  void out() { cout << x << "," << y << endl; }
};
int n, Q;
point a[maxn];
int dim;
point dir;
ll sqrtl(ll x) {
  ll y = sqrt(x);
  while ((y + 1) * (y + 1) <= x)
    y++;
  while (y > 0 && (y - 1) * (y - 1) >= x)
    y--;
  return y;
}
void solve_query() {
  point p, q;
  p.in();
  q.in();
  if (dim == 0) {
    if ((p - a[1]).len2() < (q - a[1]).len2()) {
      puts("no");
      return;
    }
    if ((p - a[1]).len2() > 0 && (p - a[1]).det(q - a[1]) != 0) {
      puts("no");
      return;
    }
    puts("yes");
  } else if (dim == 2) {
    puts("yes");
  } else {
    assert(dim == 1);
    ll pd = abs((a[2] - a[1]).det(p - a[1]));
    ll qd = abs((a[2] - a[1]).det(q - a[1]));
    if (pd < qd) {
      puts("no");
    } else if (pd == 0 || qd < pd) {
      puts("yes");
    } else {
      assert(pd == qd && pd > 0);

      for (int i = 0; i < 2; i++) {
        assert(dir.det(q - a[1]) != 0);
        ll t = (p - a[1]).det(q - a[1]) / -dir.det(q - a[1]);
        if ((p + dir * t - q).len2() == 0) {
          puts("yes");
          return;
        }
        p = a[1] + a[1] - p;
      }
      puts("no");
    }
  }
}
ll gcd(ll x, ll y) { return y == 0 ? x : gcd(y, x % y); }
int main() {
  scanf("%d%d", &n, &Q);
  for (int i = 1; i <= n; i++) {
    a[i].in();
  }
  dim = n >= 2;
  if (n >= 3) {
    for (int i = 3; i <= n; i++) {
      if ((a[2] - a[1]).det(a[i] - a[1]) != 0) {
        dim = 2;
        break;
      }
    }
  }
  if (dim == 1) {
    ll g = 0;
    for (int i = 2; i <= n; i++) {
      g = gcd(g, (a[i] - a[1]).len2());
    }
    assert(g != 0);
    ll multi = (a[2] - a[1]).len2() / g;
    ll sm = sqrtl(multi);
    assert(sm * sm == multi);
    dir = (a[2] - a[1]) / sm;

    assert(dir.len2() > 0);
  }
  for (int i = 1; i <= Q; i++) {
    solve_query();
  }
  return 0;
}