/*
 * Problem URL : https://codeforces.com/problemset/problem/1984/C2
 * Submit Date : 2025-08-13
 */

#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
int T, n;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> T;
  while (T--) {
    cin >> n;
    long long a[4] = {0, 1, 0, 1}, b[4];
    for (int i = 0; i < n; i++) {
      int w;
      cin >> w;
      b[0] = max(abs(a[0] + w), abs(a[2] + w));
      b[1] = 0;
      if (b[0] == abs(a[0] + w))
        b[1] = (b[1] + a[1]) % mod;
      if (b[0] == a[0] + w)
        b[1] = (b[1] + a[1]) % mod;
      if (a[0] != a[2] && b[0] == abs(a[2] + w))
        b[1] = (b[1] + a[3]) % mod;
      b[2] = a[2] + w;
      b[3] = a[3];
      if (b[2] >= 0)
        b[3] = b[3] * 2 % mod;
      memcpy(a, b, sizeof(b));
    }
    cout << b[1] << '\n';
  }
}