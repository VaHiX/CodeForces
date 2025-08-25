/*
 * Problem URL : https://codeforces.com/problemset/problem/2078/F
 * Submit Date : 2025-08-22
 */

#include <algorithm>
#include <iostream>

using namespace std;

const int MOD = 998244353;
const int INV4 = 1LL * (MOD + 1) * (MOD + 1) / 4 % MOD;

int t;
int n, q;
string s;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  for (cin >> t; t--;) {
    cin >> n >> q;
    cin >> s;
    int cnt = count(begin(s), end(s), '0');
    long long cur = 1LL * n * (n + 1) / 2 + 2LL * cnt * (cnt - n) - 1;
    int p2 = 1;
    for (int i = 1; i < n; i++)
      if ((p2 += p2) >= MOD)
        p2 -= MOD;
    for (int i = 1, x; i <= q; i++) {
      cin >> x;
      if ((s[--x] ^= 1) == '0')
        cur += 4 * cnt++ - 2 * (n - 1);
      else
        cur -= 4 * cnt-- - 2 * (n + 1);
      cout << cur % MOD * p2 % MOD * INV4 % MOD << '\n';
    }
  }
  return 0;
}
