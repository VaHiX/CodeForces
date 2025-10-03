/*
 * Problem URL : https://codeforces.com/contest/449/problem/A
 * Submit Date : 2025-09-06
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
ll n, m, k, ans = 0;
int main() {
  cin >> n >> m >> k;
  if (n > m) {
    ll t = n;
    n = m;
    m = t;
  }
  if (k > n + m - 2) {
    cout << -1 << endl;
    return 0;
  }
  if (k < m)
    cout << max(m / (k + 1) * n, n / (k + 1) * m) << endl;
  else
    cout << (n / (k + 2 - m)) << endl;
  return 0;
}
