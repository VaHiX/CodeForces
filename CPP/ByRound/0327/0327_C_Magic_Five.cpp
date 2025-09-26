/*
 * Problem URL : https://codeforces.com/contest/327/problem/C
 * Submit Date : 2025-09-06
 */

#include <bits/stdc++.h>
using namespace std;
#define ll long long
using namespace std;
ll L, K, t = 1, x, y, z, ans, MOD = 1e9 + 7;
string S;

ll exp(ll e) {
  if (e == 0)
    return 1;
  return e % 2 ? (exp(e - 1) * 2) % MOD : (exp(e / 2) * exp(e / 2)) % MOD;
}

ll f(ll e) {
  if (e == 0)
    return 1;
  return e % 2 ? (f(e / 2) * (exp(((e / 2) + 1) * L) + 1)) % MOD
               : (f(e - 1) * exp(L) + 1) % MOD;
}

int main() {
  cin >> S >> K;
  L = S.length();
  for (int i = 0; i < L; i++, t = (t * 2) % MOD)
    if (S[i] == '0' || S[i] == '5')
      x = (x + t) % MOD;
  ans = (x * f(K - 1)) % MOD;
  cout << ans;
}
