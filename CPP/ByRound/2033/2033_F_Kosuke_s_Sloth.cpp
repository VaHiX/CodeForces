/*
 * Problem URL : https://codeforces.com/contest/2033/problem/F
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll M = 1e9 + 7;
int main() {
  int T;
  cin >> T;
  while (T--) {
    ll n, k;
    cin >> n >> k;
    n %= M;
    ll a = 1, b = 0, c, p = 1;
    while (a % k)
      c = a, a = (a + b) % k, b = c, p++;
    cout << p * n % M << endl;
  }
}