/*
 * Problem URL : https://codeforces.com/problemset/problem/2126/D
 * Submit Date : 2025-08-08
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define fast_io                                                                \
  ios::sync_with_stdio(false);                                                 \
  cin.tie(nullptr);

void solve() {
  int n, k;
  int l, r, real, max;
  cin >> n >> k;
  vector<tuple<int, int, int>> casionos(n);
  vector<bool> satisfied(n);
  max = k;
  for (int i = 0; i < n; i++) {
    cin >> l >> r >> real;
    if (l <= k && k <= r) {
      casionos[i] = {real, l, r};
      if (real > max)
        max = real;
    } else
      casionos[i] = {real, l, r};
  }
  sort(casionos.begin(), casionos.end());
  for (int i = 0; i < n; i++) {
    if (get<0>(casionos[i]) > max && get<1>(casionos[i]) <= max &&
        max <= get<2>(casionos[i])) {
      max = get<0>(casionos[i]);
    }
  }
  cout << max << "\n";
}

int32_t main() {
  fast_io;
  int t = 1;
  cin >> t;
  while (t--)
    solve();
}
