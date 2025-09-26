// Problem: CF 2124 F1 - Appending Permutations (Easy Version)
// https://codeforces.com/contest/2124/problem/F1

/*
Problem: Count valid permutations of length n that can be constructed by appending cyclic shifts of [1..s] 
         such that m restrictions (a[i] != x) are satisfied. Modulo 998244353.

Algorithms/Techniques:
- Dynamic Programming with state tracking for valid configurations
- Preprocessing of forbidden values using bitmask or direct check

Time Complexity: O(n^4) per test case due to nested loops over segments and checks
Space Complexity: O(n^2) for DP arrays and visited matrix

*/

#include <iostream>
#include <string.h>
using namespace std;
#define int long long
#define mod 998244353
int t, n, m, vis[101][101], dp[101], dp2[101][101];

// check if a valid segment can be appended from position x to y with starting point st
bool check(int x, int y, int st) {
  int now = 0;
  // Check the prefix part that goes from st to y
  for (int i = st; i <= y; i++)
    if (vis[i][++now])  // If position i now has a forbidden constraint
      return false;
  // Check suffix part that goes from x to st-1
  for (int i = x; i < st; i++)
    if (vis[i][++now])  // If position i now has a forbidden constraint
      return false;
  return true;
}

signed main() {
  cin >> t;
  while (t--) {
    memset(vis, 0, sizeof(vis));   // Reset forbidden positions
    memset(dp, 0, sizeof(dp));     // Reset dp array
    memset(dp2, 0, sizeof(dp2));   // Reset dp2 array

    cin >> n >> m;  // Read length of array and number of restrictions
    
    // Mark forbidden values in vis matrix
    for (int i = 1, id, x; i <= m; i++)
      cin >> id >> x, vis[id][x] = 1;

    dp[0] = 1;  // Base case: one way to form empty array

    // For each possible suffix length i
    for (int i = 1; i <= n; i++) {
      // Try all starting segment positions j from 1 to i
      for (int j = 1; j <= i; j++)
        // Try all cutoffs k from j to i
        for (int k = j; k <= i; k++)
          if (check(j, i, k)) {
            // Add number of ways to construct previous part (j-1)
            // Minus contribution from earlier dp2 state if j != k
            dp[i] += dp[j - 1] - dp2[j - 1][i - k + 1] * (j != k),
            dp[i] = (dp[i] % mod + mod) % mod;  // Ensure non-negative and modulo
          }

      // Update dp2 for new valid segments ending at i
      for (int j = 1; j <= i; j++)
        if (check(j, i, j))  // If segment from j to i with start at j is valid
          dp2[i][i - j + 1] += dp[j - 1], dp2[i][i - j + 1] %= mod;
    }

    cout << dp[n] << "\n";  // Output result for current test case
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/