/*
 * Problem URL : https://codeforces.com/problemset/problem/2090/E1
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>

using namespace std;
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int T;
  cin >> T;

  while (T--) {
    int n, k;
    cin >> n >> k;

    vector<int> a(2 * n), b(2 * n);
    for (int i = 0; i < n; i++)
      cin >> a[i];
    for (int i = 0; i < n; i++)
      cin >> b[i];
    for (int i = 0; i < n; i++)
      a[i + n] = a[i], b[i + n] = b[i];

    long long gap = 0, res = 0;
    for (int l = 0, r = 0; r < 2 * n; r++) {
      gap += a[r] - b[r];
      if (gap <= 0)
        res = max(res, r - l + 1LL), l = r + 1, gap = 0;
    }

    cout << res << "\n";
  }
}