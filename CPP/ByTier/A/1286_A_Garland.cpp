// Problem: CF 1286 A - Garland
// https://codeforces.com/contest/1286/problem/A

/*
 * Problem: Garland
 * Purpose: Minimize the complexity of a garland by placing removed bulbs back.
 *          Complexity is defined as the number of adjacent pairs with different parity.
 * 
 * Algorithms/Techniques:
 *   - Dynamic Programming with states: dp[i][j][0] and dp[i][j][1]
 *     where i is the current bulb position, j is the count of even numbers placed so far,
 *     and the last bit indicates if the last placed bulb was even (0) or odd (1).
 * 
 * Time Complexity: O(n^3)
 * Space Complexity: O(n^2)
 */

#include <algorithm>
#include <iostream>

using namespace std;
#define f(i, a, b) for (int i = a; i < b; i++)
int n, dp[103][103][2], a[103], z;
int main() {
  cin >> n;
  f(i, 1, n + 1) cin >> a[i]; // Read the garland configuration
  f(i, 0, 103) { 
    f(j, 0, 103) 
      dp[i][j][0] = dp[i][j][1] = 1e9; // Initialize DP table with large values
  }
  dp[0][0][0] = 0; // Base case: no bulbs placed, last bulb even (0)
  dp[0][0][1] = 0; // Base case: no bulbs placed, last bulb odd (1)
  f(i, 1, n + 1) { // Iterate through each bulb position
    f(j, 0, i + 1) { // j represents number of even numbers placed up to now
      if (a[i] % 2 == 0) // If current bulb is even
        dp[i][j][0] = min(dp[i - 1][j - 1][0], dp[i - 1][j - 1][1] + 1); // Even bulb placed, update accordingly
      if (a[i] % 2 == 1 || a[i] == 0) // If current bulb is odd or was removed (0)
        dp[i][j][1] = min(dp[i - 1][j][0] + 1, dp[i - 1][j][1]); // Odd bulb placed
    }
  }
  cout << min(dp[n][n / 2][0], dp[n][n / 2][1]); // Output the minimum complexity
}


// https://github.com/VaHiX/codeForces/