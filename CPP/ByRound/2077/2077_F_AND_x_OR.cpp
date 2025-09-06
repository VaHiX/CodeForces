/*
 * Problem URL : https://codeforces.com/problemset/problem/2077/F
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define mp make_pair
#define vt vector
using namespace std;

ll powmod(ll base, ll exponent, ll mod) {
  ll ans = 1;
  if (base < 0)
    base += mod;
  while (exponent) {
    if (exponent & 1)
      ans = (ans * base) % mod;
    base = (base * base) % mod;
    exponent /= 2;
  }
  return ans;
}
ll gcd(ll a, ll b) {
  if (b == 0)
    return a;
  else
    return gcd(b, a % b);
}

const int INF = 2e9;
const ll INFLL = 4e18;
const int mod = 998244353;
const int ul = 1e6 + 1;

vt<int> sos(const vt<int> &a) {
  int n = a.size();
  vt<int> ans = a;
  for (int i = 1; i < n; i <<= 1) {
    for (int j = 0; j < n; j += (i << 1)) {
      for (int k = j; k < j + i; k++) {
        ans[k + i] += ans[k];
      }
    }
  }
  return ans;
}

vt<int> sos2(const vt<int> &a) {
  int n = a.size();
  vt<int> ans = a;
  for (int i = 1; i < n; i <<= 1) {
    for (int j = 0; j < n; j += (i << 1)) {
      for (int k = j; k < j + i; k++) {
        ans[k] += ans[k + i];
      }
    }
  }
  return ans;
}

void solve() {
  int n, m;
  cin >> n >> m;
  vt<int> a(n), b(n);
  for (int &i : a)
    cin >> i;
  for (int &i : b)
    cin >> i;
  int gg = 1;
  while (gg <= m)
    gg <<= 1;
  vt<int> occ_b(gg);
  for (int &i : b) {
    if (++occ_b[i] > 1) {
      cout << "0\n";
      return;
    }
  }
  vt<int> sos_b = sos(occ_b);
  vt<int> temp = sos2(occ_b);
  for (int i = 0; i < gg; i++)
    sos_b[i] += temp[i];

  int ans = m, mn = -INF;
  ll manhattan = 0;
  for (int i = 0; i < n; i++)
    manhattan += abs(a[i] - b[i]);
  if (ans > manhattan)
    ans = manhattan;

  sort(a.begin(), a.end());
  sort(b.begin(), b.end());

  for (int i = 0; i < gg; i++) {
    if (occ_b[i] > 0 && sos_b[i] > 2 * occ_b[i]) {
      cout << "0\n";
      return;
    }
    if (sos_b[i] > 0) {
      if (sos_b[i] > 1 || (i & mn) != mn)
        ans = min(ans, i - mn);
    }
    if (occ_b[i] > 0)
      mn = i;
  }
  cout << ans << "\n";
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int t = 1;
  cin >> t;
  while (t--)
    solve();
  return 0;
}