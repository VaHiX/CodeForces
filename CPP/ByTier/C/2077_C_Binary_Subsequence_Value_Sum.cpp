/*
 * Problem URL : https://codeforces.com/problemset/problem/2077/C
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
using namespace std;
long long n, m, l, T, ss, su, a1;
const long long k = 998244353, n2 = (k + 1) / 2;
string a;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> T;
  for (int u = 1; u <= T; u++) {
    cin >> n >> m;
    ss = 1;
    cin >> a;
    su = 0;
    su += a[0] - '0';
    for (int i = 1; i <= n - 1; i++)
      ss = ss * 2 % k, su += a[i] - '0';
    su = su * 2 - n;
    for (int i = 1; i <= m; i++) {
      cin >> a1;
      if (a[a1 - 1] == '0')
        a[a1 - 1] = '1', su += 2;
      else
        a[a1 - 1] = '0', su -= 2;
      cout << ss * ((su * su + n - 2 + k) % k) % k * n2 % k * n2 % k * n2 % k
           << '\n';
    }
  }
}
