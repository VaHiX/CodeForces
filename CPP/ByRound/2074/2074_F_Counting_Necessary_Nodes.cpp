/*
 * Problem URL : https://codeforces.com/problemset/problem/2074/F
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>

void solve() {
  int l1, r1, l2, r2;
  std::cin >> l1 >> r1 >> l2 >> r2;

  long long res = 1ll * (r1 - l1) * (r2 - l2);
  while (true) {
    l1 = (l1 + 1) / 2;
    r1 /= 2;
    l2 = (l2 + 1) / 2;
    r2 /= 2;
    if (l1 == r1 || l2 == r2) {
      break;
    }
    res -= 3ll * (r1 - l1) * (r2 - l2);
  }
  std::cout << res << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}