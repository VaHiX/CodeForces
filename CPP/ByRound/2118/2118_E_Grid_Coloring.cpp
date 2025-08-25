/*
 * Problem URL : https://codeforces.com/problemset/problem/2118/E
 * Submit Date : 2025-08-14
 */

#include <bits/stdc++.h>

using namespace std;

int t, n, m;

int main() {
  cin >> t;
  while (t--) {
    cin >> n >> m;
    vector<array<int, 4>> pos;
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++) {
        int di = abs(i - (n + 1) / 2);
        int dj = abs(j - (m + 1) / 2);
        array<int, 4> node = {max(di, dj), di + dj, i, j};
        pos.emplace_back(node);
      }
    sort(pos.begin(), pos.end());
    for (auto tmp : pos)
      cout << tmp[2] << ' ' << tmp[3] << '\n';
  }
  return 0;
}