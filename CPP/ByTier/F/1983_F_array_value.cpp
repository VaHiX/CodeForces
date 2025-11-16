// Problem: CF 1983 F - array-value
// https://codeforces.com/contest/1983/problem/F

/*
 * Problem: Find the k-th smallest XOR value among all subarrays of length >= 2
 *
 * Algorithm:
 * - Use a trie-based approach with bit manipulation to efficiently compute
 *   the minimum XOR value for subarrays.
 * - Process bits from most significant to least significant.
 * - For each bit level, maintain a dynamic programming array to track
 *   the earliest index where a certain prefix XOR occurs.
 * - Use a greedy strategy to determine which bit should be set in the final answer.
 *
 * Time Complexity: O(30 * n) = O(n) where n is the length of the array
 * Space Complexity: O(n) for auxiliary arrays and hash map
 */
#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <utility>

using namespace std;
#define int int64_t
#define pb push_back
const int lim = 2e5 + 100;
int mod = 1e9 + 7;
using pii = pair<int, int>;

void solve() {
  int n, k;
  cin >> n >> k;
  int a[n];
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  int cur = n * (n - 1) / 2; // Total number of subarrays of length >= 2
  int globdp[n], needmax[n]; // Global DP and needed max index for pruning
  bool donewith[n]; // Flag to track processed indices
  for (int i = 0; i < n; i++) {
    globdp[i] = i + 1; // Initialize global DP with next index
    needmax[i] = n; // Initialize needed max with n
    donewith[i] = 0; // Initialize done flag
  }
  int ans = 0; // Final result
  for (int i = 30; 0 <= i; i--) { // Process from MSB to LSB
    int dp[n];
    unordered_map<int, int> mp; // Hash map for prefix tracking
    dp[n - 1] = n; // Base case: last index
    mp[a[n - 1] >> i] = n - 1; // Insert last element's prefix
    int toremove = 0; // Number of subarrays to remove for this bit
    for (int j = n - 2; 0 <= j; j--) {
      dp[j] = dp[j + 1]; // Initialize with next index
      if (mp.count(a[j] >> i)) // If prefix exists
        dp[j] = min(dp[j], mp[a[j] >> i]); // Update with minimal index
      mp[a[j] >> i] = j; // Store current index for prefix
      if (!donewith[j]) // If not processed yet
        toremove += max<int>(0, min(needmax[j], dp[j]) - globdp[j]); // Count subarrays that will be removed
    }
    if (cur - toremove < k) { // If there are not enough to remove
      ans |= 1 << i; // Set the bit in result
      for (int j = 0; j < n; j++) {
        if (globdp[j] == dp[j]) // If global DP equals local DP
          donewith[j] = 1; // Mark as done
        needmax[j] = min(needmax[j], dp[j]); // Update needed max
        a[j] &= ~(1 << i); // Clear the bit
      }
    } else {
      cur -= toremove; // Decrease count
      for (int j = n - 2; 0 <= j; j--) { // Update global DP
        if (!donewith[j])
          globdp[j] = dp[j];
      }
    }
  }
  cout << ans << "\n";
}

signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
#ifdef Local
  freopen(".in", "r", stdin);
  freopen(".out", "w", stdout);
#endif
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/