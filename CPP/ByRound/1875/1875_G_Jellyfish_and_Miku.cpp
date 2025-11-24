// Problem: CF 1875 G - Jellyfish and Miku
// https://codeforces.com/contest/1875/problem/G

/*
 * Problem: Jellyfish and Miku
 * 
 * Purpose: Find the minimum expected number of days for Jellyfish to reach city n from city 0,
 *          given constraints on the sum of road beauties.
 * 
 * Algorithm: Dynamic Programming with optimization
 * 
 * Time Complexity: O(n * m^2 / n) = O(m^2), where n is number of roads, m is max sum of beauties
 * Space Complexity: O(n * m) for the DP table
 * 
 * Approach:
 * - Use dynamic programming to compute expected number of steps.
 * - For each road, we consider assigning a beauty value to minimize the total expected time.
 * - The recurrence relation uses the fact that probability of choosing a road with beauty x
 *   is x / sum_of_beauties_of_adjacent_roads.
 * - The expectation is calculated using the formula derived from the random walk.
 * 
 * Note: The problem is solved using a specific DP transition optimized for the structure of the graph.
 */

#include <algorithm>
#include <iomanip>
#include <iostream>

using namespace std;
#define maxx 3001
double dp[maxx][maxx];
int main() {
  int m, n;
  cin >> n >> m;
  // Initialize the DP table with a large value (representing infinity)
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      dp[i][j] = 1000000000;
    }
  }
  // Base case: starting at city 0 with 0 beauty sum has 0 expected steps
  dp[0][0] = 0;
  
  // Dynamic programming transition
  // i represents the current city (0-indexed)
  // j represents the cumulative beauty sum up to city i
  for (int i = 0; i < n; i++) {
    // Optimization: limit j based on previous state
    for (int j = i; j <= m && j <= m * i / n; j++) {
      // k represents the beauty value assigned to the i-th road
      for (int k = 1; k <= (m - j) / (n - i); k++) {
        // Transition: update the expected steps to reach city i+1 with beauty sum j+k
        dp[i + 1][j + k] = min(dp[i + 1][j + k], dp[i][j] + (1.00 * j / k));
      }
    }
  }
  
  // The final answer is the expected number of days to reach city n
  // The formula combines the result from DP table with additional terms to get the full expectation
  cout << fixed << setprecision(12) << (dp[n][m] * 2 + n) << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/