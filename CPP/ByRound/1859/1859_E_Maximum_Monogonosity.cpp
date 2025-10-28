// Problem: CF 1859 E - Maximum Monogonosity
// https://codeforces.com/contest/1859/problem/E

/*
Purpose: Solve the problem of maximizing the sum of costs of non-intersecting segments with total length k.
         The cost of a segment [l, r] is defined as |b[l] - a[r]| + |b[r] - a[l]|.
         This is approached using dynamic programming with optimized space usage.

Algorithms/Techniques: Dynamic Programming with space optimization, sliding window approach
Time Complexity: O(n * k), where n is the size of arrays and k is the total length of segments.
Space Complexity: O(k), due to the use of two rows of DP arrays of size k+1 and auxiliary arrays of size k+1.

*/
#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using i8 = int8_t;
using u8 = uint8_t;
using i16 = int16_t;
using u16 = uint16_t;
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using f32 = float;
using f64 = double;
using f80 = long double;
const i64 MOD = 1000000007;
const f64 EPS = 1e-9;
void solve() {
  i64 n, k;
  cin >> n >> k;
  vector<i64> a(n);
  for (i64 i = 0; i < n; ++i)
    cin >> a[i];
  vector<i64> b(n);
  for (i64 i = 0; i < n; ++i)
    cin >> b[i];
  vector<vector<i64>> dp(2, vector<i64>(k + 1, 0)); // DP table with two rows for space optimization
  vector<i64> dp1(k + 1, 0); // Helper array for tracking max values in one pattern
  vector<i64> dp2(k + 1, 0); // Helper array for tracking max values in another pattern
  vector<i64> dp3(k + 1, 0); // Helper array for tracking max values in another pattern
  vector<i64> dp4(k + 1, 0); // Helper array for tracking max values in another pattern
  i64 idx = 1; // Toggle index for dp array
  for (i64 i = n - 1; i >= k - 1; --i) { // Iterate from the end to ensure valid segment lengths
    idx = 1 - idx; // Switch between the two rows of DP
    dp1[0] = a[i] + b[i]; // Initialize dp1 for current position
    dp2[0] = -a[i] + b[i]; // Initialize dp2 for current position
    dp3[0] = a[i] - b[i]; // Initialize dp3 for current position
    dp4[0] = -a[i] - b[i]; // Initialize dp4 for current position
    for (i64 j = 1, l = i; j <= k; ++j, --l) { // Iterate backwards through possible lengths
      dp[idx][j] = dp[1 - idx][j]; // Copy previous j-length result

      // Update dp[idx][j] by considering all valid segment combinations ending at l
      dp[idx][j] = max(dp[idx][j], dp1[j - 1] - b[l] - a[l]); // Update based on pattern 1
      dp[idx][j] = max(dp[idx][j], dp2[j - 1] + b[l] - a[l]); // Update based on pattern 2
      dp[idx][j] = max(dp[idx][j], dp3[j - 1] - b[l] + a[l]); // Update based on pattern 3
      dp[idx][j] = max(dp[idx][j], dp4[j - 1] + b[l] + a[l]); // Update based on pattern 4

      // Update auxiliary arrays for next iteration
      dp1[j] = max(dp1[j - 1], dp[idx][j] + a[l - 1] + b[l - 1]); // Update pattern 1
      dp2[j] = max(dp2[j - 1], dp[idx][j] - a[l - 1] + b[l - 1]); // Update pattern 2
      dp3[j] = max(dp3[j - 1], dp[idx][j] + a[l - 1] - b[l - 1]); // Update pattern 3
      dp4[j] = max(dp4[j - 1], dp[idx][j] - a[l - 1] - b[l - 1]); // Update pattern 4
    }
  }
  cout << dp[idx][k] << "\n"; // Result is stored in dp[idx][k]
}
int main(void) {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  i64 t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/