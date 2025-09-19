/*
 * Problem URL : https://codeforces.com/contest/1765/problem/K
 * Submit Date : 2025-09-08
 */

#include <bits/stdc++.h>
#define ll long long int
using namespace std;

int main() {
  ios::sync_with_stdio(0);
  ll n;
  cin >> n;
  ll a[n][n], sum = 0;
  for (ll i = 0; i < n; i++)
    for (ll j = 0; j < n; j++)
      cin >> a[i][j], sum += a[i][j];
  ll mn = 1e9 + 10;
  for (ll i = 0; i < n; i++) {
    mn = min(mn, a[i][n - i - 1]);
  }
  cout << sum - mn << "\n";
}