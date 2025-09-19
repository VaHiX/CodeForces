/*
 * Problem URL : https://codeforces.com/problemset/problem/2018/A
 * Submit Date : 2025-08-20
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  const int N = 2e5 + 5;
  long long t, n, k, x, sum, mx;
  for (cin >> t; t--;) {
    cin >> n >> k;
    mx = sum = 0;
    for (int i = 1; i <= n; i++)
      cin >> x, sum += x, mx = max(mx, x);
    for (int i = n; i >= 1; i--) {
      if ((sum + k) / i * i >= sum && (sum + k) / i >= mx) {
        cout << i << "\n";
        break;
      }
    }
  }
}