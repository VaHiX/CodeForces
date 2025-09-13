/*
 * Problem URL : https://codeforces.com/contest/343/problem/C
 * Submit Date : 2025-09-08
 */

#include <cstdio>
#include <vector>
typedef long long ll;

bool check(std::vector<ll> h, std::vector<ll> r, ll b) {

  ll ind(0);
  for (ll p = 0; p < h.size(); p++) {
    ll pos;
    if (r[ind] < h[p]) {
      ll candA = b - h[p] + 2 * r[ind];
      ll candB = (b + h[p] + r[ind]) / 2;
      pos = (candA > candB) ? candA : candB;
    } else {
      pos = b + h[p];
    }

    if ((r[ind] < h[p]) && (b + r[ind] < h[p])) {
      return false;
    }
    while (ind < r.size() && (r[ind] <= pos || r[ind] <= h[p])) {
      ++ind;
    }
    if (ind == r.size()) {
      return true;
    }
  }

  return false;
}

int main() {

  ll n, m;
  scanf("%lld %lld", &n, &m);
  std::vector<ll> h(n);
  for (ll p = 0; p < n; p++) {
    scanf("%lld", &h[p]);
  }
  std::vector<ll> r(m);
  for (ll p = 0; p < m; p++) {
    scanf("%lld", &r[p]);
  }

  ll left(0), right(5e10), t(7e12);

  while (left <= right) {
    ll mid = (left + right) / 2;

    if (check(h, r, mid)) {
      t = mid;
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }

  printf("%lld\n", t);

  return 0;
}
