/*
 * Problem URL : https://codeforces.com/problemset/problem/2078/D
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, T;
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> T;
  while (T--) {
    cin >> n;
    int x = 1, y = 1, z = 0, a, b;
    char p, q;
    while (n--) {
      cin >> p >> a >> q >> b;
      if (p == '+' && q == '+')
        z += a + b;
      else if (p == '+' && q == 'x')
        y += z, z = y * (b - 1) + a;
      else if (q == '+' && p == 'x')
        x += z, z = x * (a - 1) + b;
      else if (a == b)
        z += (x + y + z) * (a - 1);
      else if (a > b)
        x += z, z = x * (a - 1) + y * (b - 1);
      else if (a < b)
        y += z, z = y * (b - 1) + x * (a - 1);
    }
    cout << x + y + z << "\n";
  }
  return 0;
}