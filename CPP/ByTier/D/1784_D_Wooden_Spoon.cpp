// Problem: CF 1784 D - Wooden Spoon
// https://codeforces.com/contest/1784/problem/D

/*
 * Problem: Wooden Spoon
 * 
 * Purpose: 
 *   For a single elimination tournament with 2^n players, compute for each player
 *   how many tournament arrangements result in them winning the "Wooden Spoon" prize.
 *   The Wooden Spoon is awarded to a player who loses their first match,
 *   and each of their subsequent match losers in the path to the final also loses their match.
 *   
 * Algorithm:
 *   - Dynamic Programming with combinatorics
 *   - dp[i][j] stores number of ways to arrange players such that player j is the i-th player
 *     in the losing chain leading to the Wooden Spoon.
 *   - Factorial preprocessing for arrangement counts
 *   - Use inclusion-exclusion or recursive structure to compute DP states
 *   - Final answer for each player is multiplied by factorial of remaining arrangements
 *   
 * Time Complexity:
 *   O(n * 2^n) where n <= 20. The DP table has size up to n * 2^n, and each transition is O(1).
 *   
 * Space Complexity:
 *   O(n * 2^n) for the DP table and factorial array.
 */

#include <stdio.h>
#include <iosfwd>

#define int long long
using namespace std;
const int mod = 998244353;
int n, dp[21][1048600], s, fact[1048600];
signed main() {
  scanf("%lld", &n);
  // Initialize dp[0][1] = 2^n
  dp[0][1] = 1 << n;
  fact[0] = 1;
  // Precompute factorials
  for (int i = 1; i <= (1 << n); ++i)
    fact[i] = fact[i - 1] * i % mod;
  int i = 2;
  // Fill DP table
  for (int i = 1; i <= n; ++i) {
    int mx = (1 << n) - (1 << n - i) + 1;
    for (int j = i + 1; j <= mx; ++j)
      dp[i][j] =
          (dp[i - 1][j - 1] * (1 << n - i) + dp[i][j - 1] * (mx - j + 1)) % mod;
  }
  // Output results for each player
  for (int i = 1; i <= (1 << n); ++i)
    printf("%lld\n", dp[n][i] * fact[(1 << n) - i] % mod);
  return 0;
}


// https://github.com/VaHiX/CodeForces/