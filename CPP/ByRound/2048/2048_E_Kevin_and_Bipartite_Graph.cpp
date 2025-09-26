/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, m;
  cin >> n >> m;

  if (2 * n - 1 < m) {
    cout << "NO\n";
    return;
  } else
    cout << "YES\n";

  for (int i = 0; i < 2 * n; i++) {
    for (int j = 0; j < m; j++)
      cout << ((j + 2 * n - i) % (2 * n) + 2) / 2 << ' ';

    cout << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  while (t--)
    solve();

  return 0;
}