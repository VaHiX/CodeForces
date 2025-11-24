// Problem: CF 698 A - Vacations
// https://codeforces.com/contest/698/problem/A

/*
 * Problem: Vasya's Vacations
 * 
 * Purpose: 
 *   Find the minimum number of days Vasya will have a rest during his vacation,
 *   given constraints that he cannot do the same activity on two consecutive days.
 *   Activities per day are:
 *     0: gym closed, contest not held
 *     1: gym closed, contest held
 *     2: gym open, contest not held
 *     3: gym open, contest held
 * 
 * Approach:
 *   Dynamic Programming (DP)
 *   - dp[0][i]: min rest days if on day i Vasya rests
 *   - dp[1][i]: min rest days if on day i Vasya writes contest
 *   - dp[2][i]: min rest days if on day i Vasya does sport
 *   For each day, we compute the minimal rest days based on previous day's state,
 *   ensuring no consecutive activities of same type.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 * 
 * Algorithms/Techniques:
 *   - Dynamic Programming
 *   - State transition with constraint checking
 */

#include <cstdio>
#include <vector>
#include <algorithm>

int main() {
  const int N = 3;            // Number of activities (rest, contest, sport)
  const int INF = 10000;      // A large number representing infinity
  int n;
  scanf("%d\n", &n);          // Read number of days
  std::vector<std::vector<int>> dp(N, std::vector<int>(n + 1, 0));  // DP table
  
  for (int p = 1; p <= n; p++) {  // For each day
    int a;
    scanf("%d", &a);            // Read activity code for day p
    
    // dp[0][p] = rest on day p
    // We must rest on day p, and we can come from any previous state
    dp[0][p] = 1 + std::min(dp[0][p - 1], std::min(dp[1][p - 1], dp[2][p - 1]));
    
    // dp[1][p] = do contest on day p
    // If day p does not allow contest (a == 0 or a == 1), impossible to do contest
    dp[1][p] = (a == 0 || a == 1) ? INF : std::min(dp[0][p - 1], dp[2][p - 1]);
    
    // dp[2][p] = do sport on day p
    // If day p does not allow sport (a == 0 or a == 2), impossible to do sport
    dp[2][p] = (a == 0 || a == 2) ? INF : std::min(dp[0][p - 1], dp[1][p - 1]);
  }
  
  // Output the minimum rest days among final possible states (rest, contest, sport)
  printf("%d\n", std::min(dp[0][n], std::min(dp[1][n], dp[2][n])));
  return 0;
}


// https://github.com/VaHiX/CodeForces/