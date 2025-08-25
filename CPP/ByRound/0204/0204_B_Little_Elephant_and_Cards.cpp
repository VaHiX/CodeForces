/*
 * Problem URL : https://codeforces.com/problemset/problem/204/B
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
#define ll long long
using namespace std;
void mk() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
}
int main() {
  mk();
  ll n, ans = 1e9;
  cin >> n;
  map<ll, pair<ll, ll>> mp;
  for (int i = 0; i < n; i++) {
    ll x, y;
    cin >> x >> y;
    mp[x].first++;
    if (x != y)
      mp[y].second++;
  }
  for (auto j : mp) {
    ll a = j.second.first;
    ll b = j.second.second;
    if (a >= (n + 1) / 2) {
      cout << 0;
      return 0;
    }
    if (a + b >= (n + 1) / 2)
      ans = min(ans, (n + 1) / 2 - a);
  }
  if (ans == 1e9)
    cout << -1;
  else
    cout << ans;
}