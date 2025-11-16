// Problem: CF 1733 E - Conveyor
// https://codeforces.com/contest/1733/problem/E

/*
Algorithm: Simulation with Mathematical Pattern Recognition
Time Complexity: O(1) per query (constant time due to precomputed patterns)
Space Complexity: O(1) (fixed size 2D array of 150x150)

The problem simulates a slime moving on a conveyor belt grid with changing directions.
Key insights:
- The movement pattern repeats every 2 seconds due to direction flipping.
- We can precompute the state of the slime's position by analyzing how it spreads.
- The DP array tracks how many slimes reach each cell at different time steps.
- By comparing the final states at time t and t+1, we determine if a slime exists.
*/

#include <string.h>
#include <iostream>

using namespace std;
#define int long long
int dp[2][150][150];
signed main() {
  int T;
  cin >> T;
  while (T--) {
    int t, x, y;
    cin >> t >> x >> y;
    memset(dp, 0, sizeof(dp));
    dp[0][1][1] = t - x - y;
    dp[1][1][1] = t - x - y + 1;
    x++, y++;
    // Fill the DP table based on recurrence relation
    for (int s = 0; s <= 1; s++)
      for (int i = 1; i <= x; i++)
        for (int j = 1; j <= y; j++)
          if (i + j > 2)
            dp[s][i][j] = (dp[s][i][j - 1] + 1) / 2 + dp[s][i - 1][j] / 2;
    // Compare final states to determine if slime exists
    if (dp[1][x][y] == dp[0][x][y])
      cout << "NO" << "\n";
    else
      cout << "YES" << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/