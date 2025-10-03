/*
 * Problem URL : https://codeforces.com/contest/662/problem/A
 * Submit Date : 2025-09-04
 */

#include <bits/stdc++.h>
using namespace std;
#define ll unsigned long long
vector<ll> b;
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int n;
  cin >> n;
  ll c = 0;
  while (n--) {
    ll a, t;
    cin >> a >> t;
    a ^= t;
    c ^= t;
    for (auto &x : b)
      a = min(a, x ^ a);
    if (a)
      b.push_back(a);
  }

  for (auto &x : b)
    c = min(c, c ^ x);
  if (c) {
    cout << "1/1";
    return 0;
  }
  n = b.size();
  if (n == 63)
    cout << "223372036854775807/223372036854775808";
  else
    cout << ((1LL << n) - 1) << "/" << (1LL << n);
}