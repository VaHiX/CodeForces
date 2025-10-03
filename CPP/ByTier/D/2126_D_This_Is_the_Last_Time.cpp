// Problem: CF 2126 D - This Is the Last Time
// https://codeforces.com/contest/2126/problem/D

/*
D. This Is the Last Time
Algorithm: Greedy with sorting
Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing casino data

Approach:
1. For each casino, if it can be visited with current coins (k), store it.
2. Otherwise, still store it but mark it as not usable initially.
3. Sort all casinos by their "real" value (the number of coins they give after playing).
4. Iterate through the sorted list and simulate playing casinos to maximize coins.

Key idea:
To get maximum coins:
- We want to play casinos that give more coins first, but only if we can afford them.
- So we sort by real coin gain (descending) and process in order.
- Keep updating the available coins and play where possible.
*/

#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;
#define int long long
#define fast_io                                                                \
  ios::sync_with_stdio(false);                                                 \
  cin.tie(nullptr);

void solve() {
  int n, k;
  int l, r, real, max;
  cin >> n >> k;
  vector<tuple<int, int, int>> casionos(n); // Store {real, l, r} for each casino
  vector<bool> satisfied(n);
  max = k; // Initialize max to current coins
  for (int i = 0; i < n; i++) {
    cin >> l >> r >> real;
    if (l <= k && k <= r) {
      // If we can visit this casino now
      casionos[i] = {real, l, r};
      if (real > max)
        max = real;
    } else
      casionos[i] = {real, l, r};
  }
  sort(casionos.begin(), casionos.end()); // Sort by real value ascending
  for (int i = 0; i < n; i++) {
    if (get<0>(casionos[i]) > max && get<1>(casionos[i]) <= max &&
        max <= get<2>(casionos[i])) {
      // If we can use this casino's real value to update max
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


// https://github.com/VaHiX/codeForces/