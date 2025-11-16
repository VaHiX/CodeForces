// Problem: CF 1767 C - Count Binary Strings
// https://codeforces.com/contest/1767/problem/C

/*
 * Problem: Count Binary Strings
 * Algorithm: Dynamic Programming with Segment Checking
 * 
 * Time Complexity: O(n^4)
 * Space Complexity: O(n^2)
 * 
 * Approach:
 * - Use dynamic programming where dp[i] represents the number of valid
 *   ways to fill the first i positions of the string.
 * - For each position i, check all previous positions j (0 to i-1) to see
 *   if we can transition from dp[j] to dp[i] by appending a new segment
 *   from position j+1 to i.
 * - The check function validates whether the segment [j+1, i] adheres to
 *   the constraints defined in the input matrix s.
 * - Since we can start with either '0' or '1', the final answer is multiplied by 2.
 */

#include <stdio.h>
#include <iosfwd>

using namespace std;
const int p = 998244353;
int n, s[105][105];
int dp[105];

// Check if segment [l, r] satisfies constraints
bool check(int l, int r) {
  for (int i = 1; i <= r; i++)
    for (int j = i; j <= n; j++) {
      // If constraint is 1 (all same), but segment overlaps with [l, r] and it's not fully contained
      if (i < l && l <= j && s[i][j] == 1)
        return false;
      // If constraint is 2 (at least two different chars), but segment overlaps with [l, r] and it's not fully contained
      if (l <= i && j <= r && s[i][j] == 2)
        return false;
    }
  return true;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    for (int j = i; j <= n; j++)
      scanf("%d", &s[i][j]);
  
  // Base case: empty prefix has one way
  dp[0] = 1;
  
  // Fill dp array
  for (int i = 1; i <= n; i++)
    for (int j = 0; j < i; j++)
      // If it's valid to place segment [j+1, i], add ways
      if (check(j + 1, i))
        dp[i] = (dp[i] + dp[j]) % p;
  
  // Multiply by 2 because we can start with either 0 or 1
  printf("%d", dp[n] * 2 % p);
}


// https://github.com/VaHiX/CodeForces/