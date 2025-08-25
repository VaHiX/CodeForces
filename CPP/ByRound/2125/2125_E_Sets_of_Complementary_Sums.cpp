/*
 * Problem URL : https://codeforces.com/problemset/problem/2125/E
 * Submit Date : 2025-08-14
 */

#include <algorithm>
#include <cstdio>
#include <iostream>

#define N 200086
#define fo(a, b, c, d) for (int a = b; a <= c; a += d)
#define ro(a, b, c, d) for (int a = b; a >= c; a -= d)
#define ll long long
#define MOD 998244353ll

using namespace std;

int f[N];

void work() {
  int n, x;
  cin >> n >> x;
  if (n == 1) {
    cout << x << endl;
    return;
  } else if (n == 2) {
    cout << 1ll * x * (x - 1) / 2 % MOD << endl;
    return;
  }
  if ((ll)n * (n + 1) / 2 - 1 > x) {
    cout << 0 << endl;
    return;
  }
  int len = (x - (n * (n + 1) / 2 - 1));
  fo(i, 0, len, 1) f[i] = 0;
  f[0] = 1;
  fo(i, 1, n - 1, 1) {
    fo(j, i, len, 1) { f[j] = (f[j] + f[j - i]) % MOD; }
  }
  int ans = 0;
  fo(i, 0, len, 1) { ans = (ans + 1ll * f[i] * (len - i + 1) % MOD) % MOD; }
  cout << ans << endl;
  return;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  int T;
  cin >> T;
  while (T--)
    work();
  return 0;
}
/*
1
27 31415
*/