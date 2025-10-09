// Problem: CF 2147 E - Maximum OR Popcount
// https://codeforces.com/contest/2147/problem/E

// Problem: E. Maximum OR Popcount
// Task: Given an array of non-negative integers and multiple scenarios,
// each with a limit on operations (incrementing elements by 1), maximize
// the number of set bits in the bitwise OR of all numbers.
//
// Algorithm:
// - Precompute for all possible numbers of set bits (0 to 31) the minimum
//   number of operations needed to achieve that popcount.
// - Process each scenario by querying precomputed values to find max popcount
//   achievable within given operation limit.
//
// Time Complexity: O(N * 32 + Q * 32)
// Space Complexity: O(32) = O(1)

#include <algorithm>
#include <iostream>

using namespace std;
#define int long long
#define popc(x) __builtin_popcount(x)
const int N = 2e5 + 10, inf = 1e16 + 7;
int dp[60], a[N], n, q;

void work() {
  cin >> n >> q;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  for (int i = 0; i <= 50; i++)
    dp[i] = inf;
  int res = 0, val = 0;
  for (int i = 1; i <= n; i++)
    res |= a[i]; // Compute initial OR
  dp[popc(res)] = min(dp[popc(res)], val); // Store initial popcount cost
  for (int i = 0; i <= 31; i++) { // Iterate through all possible bit positions (0-31)
    for (int j = i; j >= 0; j--) {
      int f = 0;
      for (int k = 1; k <= n; k++)
        if (a[k] & (1ll << j))
          f = 1;
      if (f)
        continue; // Skip if bit already set in any element
      int pos = 0, ret = 0;
      for (int k = 1; k <= n; k++)
        if ((a[k] % (1ll << j)) >= ret) { // Find max value in current bit position
          pos = k;
          ret = (a[k] % (1ll << j));
        }
      val += (1ll << j) - ret; // Add cost to reach full bit set
      for (int k = 0; k < j; k++)
        if (a[pos] & (1ll << k))
          a[pos] ^= (1ll << k); // Clear lower bits
      a[pos] |= (1ll << j); // Set current bit
    }
    res = 0;
    for (int j = 1; j <= n; j++)
      res |= a[j]; // Recalculate OR after operations
    dp[popc(res)] = min(dp[popc(res)], val); // Store minimum cost to achieve popcount
  }
  while (q--) {
    int b;
    cin >> b;
    int ans = 0;
    for (int i = 0; i <= 31; i++)
      if (dp[i] <= b)
        ans = max(ans, i); // Find maximum popcount achievable with `b` operations
    cout << ans << "\n";
  }
  return;
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--)
    work();
  return 0;
}


// https://github.com/VaHiX/CodeForces/