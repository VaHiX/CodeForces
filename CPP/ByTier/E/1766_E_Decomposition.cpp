// Problem: CF 1766 E - Decomposition
// https://codeforces.com/contest/1766/problem/E

/*
 * Purpose: Computes the sum of decomposition counts for all subarrays of a given sequence.
 *          Each element in the input sequence is between 0 and 3.
 * 
 * Algorithm:
 *   - Uses dynamic programming with a rolling array to track the number of subsequences
 *     ending at each position with specific last elements (up to 3 elements tracked).
 *   - For each new element, updates the DP state based on whether the bitwise AND
 *     of the new element with existing subsequence elements is greater than 0.
 *   - Time Complexity: O(n)
 *   - Space Complexity: O(1) (fixed-size DP array)
 */

#include <string.h>
#include <iostream>

using namespace std;
#define int long long
int n, X, ans, dp[2][4][4][4]; // dp[2][4][4][4] tracks counts for up to 3-element subsequences
signed main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    int a;
    cin >> a;
    // Initialize dp for new element, incrementing count for empty subsequence
    dp[X][0][0][0]++;
    
    // Special case when element is 0, contributes to all subarrays ending at this position
    if (a == 0)
      ans += i * (n - i + 1);
    else {
      // Flip the DP index for current step
      X ^= 1;
      // Reset the new DP state
      memset(dp[X], 0, sizeof(dp[X]));
      
      // Process all previous states and carry over valid transitions
      for (int j = 0; j <= 3; j++)
        for (int k = 0; k <= 3; k++)
          for (int l = 0; l <= 3; l++)
            if (j == 0 || (j & a)) // if no previous subsequence or bitwise AND > 0
              dp[X][a][k][l] += dp[X ^ 1][j][k][l]; // Append to first subsequence
            else if (k == 0 || (k & a)) // if no second subsequence or bitwise AND > 0
              dp[X][j][a][l] += dp[X ^ 1][j][k][l]; // Append to second subsequence
            else
              dp[X][j][k][a] += dp[X ^ 1][j][k][l]; // Append to third subsequence
    }
    
    // Add contribution of current state to final result
    for (int j = 0; j <= 3; j++)
      for (int k = 0; k <= 3; k++)
        for (int l = 0; l <= 3; l++)
          ans += dp[X][j][k][l] * ((j > 0 ? 1 : 0) + (k > 0 ? 1 : 0) + (l > 0 ? 1 : 0));
  }
  cout << ans << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/