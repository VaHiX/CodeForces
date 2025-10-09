/*
 * Problem URL : https://codeforces.com/problemset/problem/1267/J
 * Submit Date : 2025-08-13
 */

#include "bits/stdc++.h"

using namespace std;
using LL = long long;

constexpr int N = 1e5 + 5;

void solve() {
  int n;
  cin >> n;

  vector<int> cnt(n + 1);
  for (int i = 1; i <= n; i++) {
    int c;
    cin >> c;
    cnt[c]++;
  }

  map<int, int> mp;
  for (int x : cnt)
    if (x)
      mp[x]++;

  int Size = mp.begin()->first;
  int ans = n;
  Size++;

  for (int d = 1; d <= Size; d++) {
    bool ok = 1;
    int T = 0;

    for (auto &[a, b] : mp) {
      int q = (a + d - 1) / d;
      if (a < q * (d - 1))
        ok = 0;
      else
        T += q * b;
    }

    if (ok) {
      ans = min(ans, T);
    }
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  while (t--)
    solve();
}