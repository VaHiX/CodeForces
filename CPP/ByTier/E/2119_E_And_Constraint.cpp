// Problem: CF 2119 E - And Constraint
// https://codeforces.com/contest/2119/problem/E

/*
E. And Constraint
time limit per test2 seconds
memory limit per test256 megabytes
wowaka & Hatsune Miku - Tosenbo

Problem Summary:
Given two sequences `a` of length n-1 and `b` of length n,
we want to find the minimum number of operations (incrementing any b[i] by 1)
such that for all i from 1 to n-1, b[i] & b[i+1] = a[i].
This is solved via dynamic programming with bit manipulation optimization.

Algorithm:
- Use dynamic programming on bits, maintaining possible values of `b[i]`
  such that previous constraints are satisfied.
- For each position, process bits from most significant to least significant,
  determining valid suffixes for current `b[i]` that satisfy:
    - b[i] & b[i+1] == a[i]
    - Constraints from earlier bits (bitmask)
- The DP state tracks: possible values of prefix and minimal cost of achieving it.

Time Complexity:
O(n * 30 * 2^k) where k is number of states (in practice limited due to bit constraints).

Space Complexity:
O(2^k) where k is number of distinct prefixes maintained in DP.

*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
struct stu {
  int x; // Current bitmask representing prefix
  long long dp; // Minimum operations needed to reach this state
};
void solve() {
  using ll = long long;
  constexpr ll inf = 0x3f3f3f3f3f3f3f3f;
  int n;
  cin >> n;
  vector<int> a(n - 1);
  vector<int> b(n);
  for (int i = 0; i < n - 1; ++i)
    cin >> a[i];
  for (int i = 0; i < n; ++i)
    cin >> b[i];
  vector<stu> f{{0, 0}}, g; // f is current states, g is next states
  for (int i = 0; i < n; ++i) {
    g.clear();
    int x = 0;
    const int target = (((i > 0) ? a[i - 1] : 0) | ((i < n - 1) ? a[i] : 0)); // Target OR of current and next constraint
    const int last = ((i > 0) ? a[i - 1] : 0); // Previous constraint for AND check
    for (int j = 30; j >= -1; --j) { // Iterate from MSB to LSB (include dummy -1 for initialization)
      int y = x | target; // Build candidate value using prefix 'x' and target bits
      if (j != -1)
        y |= (1 << j); // Try setting bit j
      if (y >= b[i]) { // Only consider valid candidates >= current b[i]
        ll mn = inf;
        for (auto l : f) {
          if ((y & l.x) != last) // Check if this value satisfies last constraint
            continue;
          mn = min(mn, l.dp + y - b[i]); // Add cost to reach this state
        }
        if (mn < inf)
          g.push_back({y, mn});
      }
      if (j != -1)
        x |= (1 << j) & b[i]; // Update prefix based on current bit of b[i]
    }
    swap(f, g); // Move to next level
  }
  ll ans{inf};
  for (auto l : f)
    ans = min(ans, l.dp);
  cout << (ans == inf ? -1 : ans) << "\n";
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/