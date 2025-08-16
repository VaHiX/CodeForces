/*
 * Problem URL : https://codeforces.com/problemset/problem/2126/E
 * Submit Date : 2025-08-08
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int t, n, m, a[N], b[N], f;

int main() {
  cin >> t;
  while (t--) {
    cin >> n;
    f = 1;
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    for (int i = 1; i <= n; i++)
      cin >> b[i];
    if (a[n] != b[1])
      f = 0;
    for (int i = 1; i < n; i++) {
      if (a[i] % a[i + 1] != 0)
        f = 0;
      if (b[i + 1] % b[i] != 0)
        f = 0;
    }
    for (int i = 1; i < n; i++) {
      if (__gcd(a[i], b[i + 1]) != a[n])
        f = 0;
    }
    if (f == 0)
      cout << "NO\n";
    else
      cout << "YES\n";
  }
  return 0;
}