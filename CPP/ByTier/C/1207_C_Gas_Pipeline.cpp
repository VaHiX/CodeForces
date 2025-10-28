// Problem: CF 1207 C - Gas Pipeline
// https://codeforces.com/contest/1207/problem/C

/*
C. Gas Pipeline
Algorithms/Techniques: Dynamic Programming
Time Complexity: O(n)
Space Complexity: O(n)

This problem involves finding the minimum cost to install a gas pipeline along a road represented as a binary string.
Each character in the string represents whether there is a crossroad (1) or not (0).
The pipeline can be at height 1 or 2, with different costs for transitions and pillar usage.
We use dynamic programming where dp[i][0] represents the minimum cost to reach position i with the pipeline at height 1,
and dp[i][1] represents the minimum cost to reach position i with the pipeline at height 2.
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>

using namespace std;
long long int t, n, a, b, dp[200010][2];
char s[200010];
int main() {
  cin >> t;
  while (t--) {
    memset(dp, 0x3f, sizeof dp); // Initialize dp array with large values
    scanf("%lld%lld%lld%s", &n, &a, &b, s + 1);
    dp[0][0] = 0; // Base case: starting at height 1 with zero cost
    for (int i = 1; i <= n; i++) {
      if (s[i] == '0') // If no crossroad at current position
        dp[i][0] = min(dp[i - 1][0] + a + b, dp[i - 1][1] + 2 * a + 2 * b); // Transition to height 1 from either height
      dp[i][1] = min(dp[i - 1][1] + a + 2 * b, dp[i - 1][0] + 2 * a + 2 * b); // Transition to height 2 from either height
    }
    cout << dp[n][0] + b << endl; // Add cost of final pillar at height 1
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/