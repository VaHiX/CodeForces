/*
 * Problem URL : https://codeforces.com/contest/396/problem/A
 * Submit Date : 2025-09-06
 */

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

ll M = 1e9 + 7;

ll powm(ll a, ll n) {
  if (n == 0)
    return 1;
  if (n & 1)
    return a * powm(a, n - 1) % M;
  return powm(a * a % M, n / 2);
}

ll inv(ll x) { return powm(x, M - 2); }

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  bitset<33333> b(0);
  vector<ll> F(33333);
  F[0] = 1;
  for (ll i = 1; i < 33333; i++)
    F[i] = (F[i - 1] * i) % M;

  for (int i = 2; i * i < 33333; i++)
    if (!b[i])
      for (int j = 2 * i; j < 33333; j += i)
        b[j] = 1;

  vector<int> P;
  for (int i = 2; i < 33333; i++)
    if (!b[i])
      P.push_back(i);

  int n, x;
  cin >> n;
  map<ll, ll> mp;

  for (int i = 0; i < n; i++) {
    cin >> x;
    for (auto &p : P)
      while (x % p == 0)
        x /= p, mp[p]++;

    if (x != 1)
      mp[x]++;
  }

  ll ats = 1;
  ll k = n;
  // stars and bars -> C(n+k-1,k-1)
  for (auto &p : mp) {
    ll n = p.second;
    ll ways = F[n + k - 1] * inv(F[k - 1]) % M * inv(F[n]) % M;
    ats = (ats * ways) % M;
  }
  cout << ats;
}
