/*
 * Problem URL : https://codeforces.com/problemset/problem/2132/D
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
#define ll long long
#define ii array<int, 2>
using namespace std;

void solve() {
  ll n;
  cin >> n;
  ll cur = 9, len = 1;
  while (n - cur * len > 0) {
    n -= cur * len;
    cur *= 10;
    len++;
  }
  string s = to_string(cur / 9 + (n - 1) / len);
  ll ans = 0;
  for (int i = 0; i < (n - 1) % len + 1; i++) {
    ans += s[i] - '0';
  }
  ll sum = 0;
  cur /= 9;
  for (int i = 0; i < s.size(); i++) {
    ll x = s[i] - '0';
    ans += x * (len - 1) * cur * 9 / 2 + x * (2 * sum + x - 1) / 2 * cur;
    cur /= 10;
    len--;
    sum += x;
  }
  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
}
