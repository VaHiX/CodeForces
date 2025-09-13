/*
 * Problem URL : https://codeforces.com/problemset/problem/2114/G
 * Submit Date : 2025-08-16
 */

#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int _;
  cin >> _;
  while (_--) {
    int n;
    ll k;
    cin >> n >> k;
    vector<ll> a(n);
    for (int i = 0; i < n; i++)
      cin >> a[i];

    vector<ll> b(n, 1), c = a;
    for (int i = 0; i < n; i++)
      while (c[i] % 2 == 0)
        c[i] /= 2, b[i] *= 2;

    vector<ll> d(n, 0), e(n, 0);
    for (int i = 1; i < n; i++) {
      d[i] = d[i - 1];
      if ((c[i] != c[i - 1]) || (b[i] > b[i - 1]))
        d[i] += b[i - 1];
      else
        d[i] += b[i - 1] - 2ll * b[i] + 1;
    }

    for (int i = n - 2; i > -1; i--) {
      e[i] = e[i + 1];
      if ((c[i] != c[i + 1]) || (b[i] > b[i + 1]))
        e[i] += b[i + 1];
      else
        e[i] += b[i + 1] - 2ll * b[i] + 1;
    }

    ll ans = 0;
    for (int i = 0; i < n; i++)
      ans = max(ans, b[i] + d[i] + e[i]);
    if (ans < k)
      cout << "NO\n";
    else
      cout << "YES\n";
  }
}