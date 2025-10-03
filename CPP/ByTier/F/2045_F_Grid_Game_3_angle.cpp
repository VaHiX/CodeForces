/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int t;
  cin >> t;
  while (t--) {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(k + 1);
    for (int i = 0; i < m; i++) {
      int r, c, x;
      cin >> r >> c >> x;
      x %= (k + 1);
      a[r % (k + 1)] ^= x;
    }
    int f = 0;
    for (int i = 0; i < k + 1; i++) {
      if (a[i] != 0) {
        f = 1;
      }
    }
    if (!f) {
      cout << "Kamu\n";
    } else {
      cout << "Anda\n";
    }
  }

  return 0;
}