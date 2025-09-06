/*
 * Problem URL : https://codeforces.com/problemset/problem/2072/G
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int P = 1e9 + 7;
ll n, k, ans;
ll sum(ll l, ll r) { return (r + l) * (r - l + 1) / 2; }
ll sum2(ll x) { return x * (x + 1) * (x + x + 1) / 6; }
void solve() {
  cin >> n >> k;
  if (n == 1) {
    cout << (k - 1) % P << endl;
    return;
  }
  if (k > n) {
    ans = (k - n) % P * n % P;
    k = n;
  } else {
    ans = 0;
  }
  for (ll r = k, l;; r = l - 1) {
    ll t = n / r;
    l = n / (t + 1) + 1;
    if (t >= l) {
      k = r;
      break;
    }
    ans =
        (ans + n * sum(l, r) - t * (sum2(r) - sum2(l - 1)) + t * (r - l + 1)) %
        P;
  }
  for (ll r = k; r >= 2; r--) {
    ll x = n, sum = 0;
    while (x) {
      sum *= r;
      sum += x % r;
      x /= r;
    }
    ans += sum;
    ans -= ans < P ? 0 : P;
  }
  cout << ans << endl;
}
int main() {
  int T;
  cin >> T;
  while (T--)
    solve();
  return 0;
}