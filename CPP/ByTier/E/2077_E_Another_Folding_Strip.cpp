/*
 * Problem URL : https://codeforces.com/problemset/problem/2077/E
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll N = 200007, MOD = 998244353;
ll T, n, a[N], ans, stk[N], top, L[N], R[N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> T;
  stk[0] = -1;
  while (T--) {
    cin >> n;
    ans = 0;
    for (int i = 1; i <= n; ++i) {
      cin >> a[i];
      if (i & 1)
        a[i] += a[i - 1];
      else
        a[i] = a[i - 1] - a[i];
    }
    for (int i = 1; i <= n; ++i)
      R[i] = n + 1;
    top = 0;
    for (int i = 1; i <= n; ++i) {
      while (top && a[stk[top]] < a[i])
        R[stk[top--]] = i;
      L[i] = stk[top];
      stk[++top] = i;
    }
    for (int i = 1; i <= n; ++i)
      (ans += (R[i] - i) * (i - L[i]) % MOD * (a[i] % MOD)) %= MOD;
    top = 0;
    for (int i = 1; i <= n; ++i)
      R[i] = n + 1;
    for (int i = 0; i <= n; ++i) {
      while (top && a[stk[top]] >= a[i])
        R[stk[top--]] = i;
      L[i] = stk[top];
      stk[++top] = i;
    }
    for (int i = 1; i <= n; ++i)
      (ans -= (R[i] - i) * (i - L[i]) % MOD * (a[i] % MOD)) %= MOD;
    cout << (ans + MOD) % MOD << '\n';
  }
  return 0;
}