/*
 * Problem URL : https://codeforces.com/contest/1662/problem/L
 * Submit Date : 2025-09-08
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz = 2e5 + 5;

int a[sz], t[sz];

int main() {
  int n;
  ll v;
  cin >> n >> v;
  for (int i = 0; i < n; i++)
    scanf("%d", &t[i]);
  for (int i = 0; i < n; i++)
    scanf("%d", &a[i]);
  vector<pair<ll, ll>> p;
  for (int i = 0; i < n; i++) {
    if (t[i] * v - abs(a[i]) < 0)
      continue;
    p.emplace_back(t[i] * v - a[i], t[i] * v + a[i]);
  }
  sort(p.begin(), p.end());
  vector<ll> b;
  for (auto &[x, y] : p) {
    if (b.empty() || b.back() <= y)
      b.push_back(y);
    else
      *upper_bound(b.begin(), b.end(), y) = y;
  }
  cout << b.size();
}

/*

## aj - ai <= (tj - ti) * v

=> aj - tj * v <= ai - ti * v

=> tj * v - aj >= ti * v - ai - (i)

## ai - aj <= (tj - ti) * v

=> ai + ti * v <= aj + tj * v - (ii)

*/