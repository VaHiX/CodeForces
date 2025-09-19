/*
 * Problem URL : https://codeforces.com/contest/963/problem/A
 * Submit Date : 2025-09-04
 */

#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll md = 1e9 + 9;
ll n, a, b, k, ans, sum, xa, xi, x, ia;
ll ksm(ll a, ll b) {
  ll re = 1;
  a %= md;
  while (b) {
    if (b & 1) {
      re = re * a % md;
    }
    a = a * a % md;
    b /= 2;
  }
  return re;
}
string s;
int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> a >> b >> k;
  cin >> s;
  ans = 0;
  x = ksm(a, n);
  ia = ksm(a, md - 2), xa = 1;
  for (int i = 0; i < k; i++) {
    if (s[i] == '+') {
      ans = (ans + x * xa % md) % md;
    } else {
      ans = (ans + md - x * xa % md) % md;
    }
    x = x * ia % md, xa = xa * b % md;
  }
  xa = 1;
  sum = 0;
  xi = ksm(b * ia, k);
  x = (n + 1) / k;
  if (xi == 1) {
    cout << ans * x % md << endl;
  } else {
    ll xxx = (1 + md - ksm(xi, x));
    ll xxx1 = ksm(1 + md - xi, md - 2);
    cout << ans * xxx % md * xxx1 % md << endl;
  }
}