/*
 * Problem URL : https://codeforces.com/problemset/problem/2111/D
 * Submit Date : 2025-08-17
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int a[N];
void solve() {
  int n, m;
  cin >> m >> n;
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  sort(a, a + n);
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < 6; ++j) {
      if ((i + j) % 2 == 0)
        cout << a[i / 2] << ' ';
      else
        cout << a[n - i / 2 - 1] << ' ';
    }
    cout << '\n';
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int _;
  cin >> _;
  while (_--)
    solve();
  return 0;
}