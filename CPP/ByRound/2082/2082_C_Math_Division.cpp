/*
 * Problem URL : https://codeforces.com/problemset/problem/2082/C
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll inv2 = 5e8 + 4, mod = 1e9 + 7;
void solve() {
  int n;
  cin >> n;
  vector<int> dp(n);
  string s;
  cin >> s;
  ll ans = 0;
  for (int i = n - 1; i > 0; i--)
    ans = (ans + (s[i] == '1')) * inv2 % mod;
  cout << (n - 1 + ans) % mod << '\n';
  return;
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}