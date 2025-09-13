/*
 * Problem URL : https://codeforces.com/problemset/problem/2096/E
 * Submit Date : 2025-08-20
 */

#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int T;

int n;
i64 ans, a, b;
string s;

void solve() {
  a = b = ans = 0;

  cin >> n >> s;

  for (int i = 0; i < n; ++i) {
    if (s[i] == 'B') {
      a++;
      b += !((i + 1) & 1);
      ans += i + 1 - a;
    }
  }

  cout << (ans + abs(a / 2 - b)) / 2 << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> T;
  while (T--)
    solve();

  return 0;
}