/*
 * Problem URL : https://codeforces.com/problemset/problem/2081/A
 * Submit Date : 2025-08-20
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll inv2 = 5e8 + 4, mod = 1e9 + 7;
ll t, n;
char s[1000009];
int main() {
  cin >> t;
  while (t--) {
    cin >> n;
    scanf("%s", s + 1);
    ll ans = 0;
    for (ll i = n; i > 1; i -= 1) {
      ans = (ans + (s[i] == '1')) * inv2 % mod;
    }
    printf("%lld\n", (n - 1 + ans) % mod);
  }
  return 0;
}