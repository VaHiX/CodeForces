// Problem: CF 761 C - Dasha and Password
// https://codeforces.com/contest/761/problem/C

/*
 * Problem: Dasha and Password
 * 
 * Purpose: 
 *   Find the minimum number of operations to make a password string valid,
 *   where a valid password must contain at least one digit, one lowercase letter,
 *   and one of the special characters '#', '*', or '&'.
 * 
 * Approach:
 *   - Dynamic Programming with bitmasking:
 *     - Use a 2D DP array `dp[i][mask]` where `i` is the current character position
 *       and `mask` represents which types of characters (digit, lowercase, special)
 *       are already present in the prefix.
 *     - For each character in the password, we can choose any of the `m` positions
 *       in the corresponding string. We calculate the minimum moves needed to reach
 *       each position, considering it's cyclic.
 *     - The final result is `dp[n][7]`, where 7 = 111 in binary (all three character types present).
 * 
 * Time Complexity: O(n * m^2)
 *   - n: length of password
 *   - m: length of each string assigned to characters
 *   - For each character position, we check all m positions in the string,
 *     and for each, we compute the minimal moves to reach the desired position.
 * 
 * Space Complexity: O(n * 8) = O(n)
 *   - The bitmask uses only 3 bits, so 2^3 = 8 states are possible.
 *   - Only one row (i=0 to n) of dp is needed at a time.
 */

#include <stdio.h>

const int N = 55;
const int inf = 1e9 + 7;
char s[N];
int dp[N][1 << 3], val[N];
int min(int a, int b) { return a > b ? b : a; }
int main() {
  int n, m, i, j, k;
  scanf("%i %i", &n, &m);
  // Initialize dp table with infinity
  for (i = 0; i < N; i++)
    for (j = 0; j < (1 << 3); j++)
      dp[i][j] = inf;
  dp[0][0] = 0; // Base case: no characters selected, 0 operations
  for (i = 1; i <= n; i++) {
    scanf("%s", s + 1);
    for (j = 1; j <= m; j++) {
      // Classify the character at position j into a category (0=digit, 1=lowercase, 2=special)
      if (s[j] >= '0' && s[j] <= '9')
        val[j] = 0;
      else if (s[j] >= 'a' && s[j] <= 'z')
        val[j] = 1;
      else
        val[j] = 2;
      // Update DP for all possible masks
      for (k = 0; k < (1 << 3); k++) {
        // Compute minimal operations to reach this state at position j
        // Move cost: min of left or right move in cyclic string
        int cost = min(j - 1, m - j + 1);
        // Transition: old_dp + move_cost
        dp[i][k | (1 << val[j])] =
            min(dp[i][k | (1 << val[j])], dp[i - 1][k] + cost);
      }
    }
  }
  printf("%i\n", dp[n][7]); // Final answer: all character types present
  return 0;
}


// https://github.com/VaHiX/CodeForces/