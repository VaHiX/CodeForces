/*
 * Problem URL : https://codeforces.com/problemset/problem/2086/E
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
using ll = long long;
map<ll, ll> mp[130];
ll base[35];
ll query(ll n, ll k) {
  //	cout<<n<<" "<<k<<'\n';
  if (k >= 130 || k <= 0 || n == 0)
    return 0;
  if (mp[k].find(n) != mp[k].end())
    return mp[k][n];
  long long ans = 0, c;
  ll now = 30;
  while (base[now] > n) {
    now--;
  }
  c = base[now];
  for (ll i = 0; i <= n; i += c) {
    if (i + c <= n)
      ans += query(c - 1, k - i / c);
    else
      ans += query(n % c, k - i / c);
    if (k - i / c == 0)
      ans++;
  }
  mp[k][n] = ans;
  return ans;
}
int main() {
  base[0] = 1;
  for (int i = 1; i < 31; i++) {
    base[i] = base[i - 1] * 4 + 1;
  }
  int T;
  cin >> T;
  while (T--) {
    ll l, r, k;
    cin >> l >> r >> k;
    cout << query(r, k) - query(l - 1, k) << '\n';
  }
}