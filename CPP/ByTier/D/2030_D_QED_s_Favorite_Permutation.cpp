/*
 * Problem URL : https://codeforces.com/contest/2030/problem/D
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 2;
int T, n, q, p[N], cnt;
bool f[N], b[N];
string s;
bool check(int x) { return !f[x] && !b[x] && b[x + 1]; }
int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (cin >> T; T--;) {
    cin >> n >> q;
    cnt = 0;
    for (int i = 1, x = 0; i <= n; ++i) {
      cin >> p[i];
      x = max(x, p[i]);
      f[i] = x == i;
    }
    cin >> s;
    for (int i = 0; i < n; ++i)
      b[i + 1] = s[i] == 'R';
    for (int i = 1; i < n; ++i)
      cnt += check(i);
    for (int i; q--;) {
      cin >> i;
      cnt -= check(i - 1) + check(i);
      b[i] ^= 1;
      cnt += check(i - 1) + check(i);
      cout << (cnt ? "NO\n" : "YES\n");
    }
  }
  return 0;
}