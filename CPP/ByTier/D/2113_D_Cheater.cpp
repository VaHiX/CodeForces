/*
 * Problem URL : https://codeforces.com/problemset/problem/2113/D
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int N = 2e5 + 5;
int t, n, a[N], sa[N], b[N], mx[N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    cin >> n, a[0] = sa[0] = b[0] = 1e9, mx[n + 1] = 0;
    for (int i = 1, x; i <= n; i++) {
      cin >> x, mx[i] = x, a[i] = a[i - 1], sa[i] = sa[i - 1];
      if (x < a[i])
        sa[i] = a[i], a[i] = x;
      else if (x < sa[i])
        sa[i] = x;
    }
    for (int i = n; i; i--)
      mx[i] = max(mx[i + 1], mx[i]);
    for (int i = 1, x; i <= n; i++)
      cin >> x, b[i] = min(b[i - 1], x);
    for (int i = n; ~i; i--)
      if (b[n - i + 1] < sa[i] &&
          (b[n - i + 1] < a[i] || b[n - i + 1] < mx[i + 1])) {
        cout << i << "\n";
        break;
      }
  }
  return 0;
}