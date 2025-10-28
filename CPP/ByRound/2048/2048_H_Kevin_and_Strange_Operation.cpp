// Problem: CF 2048 H - Kevin and Strange Operation
// https://codeforces.com/contest/2048/problem/H

/*
H. Kevin and Strange Operation
Algorithm: Dynamic Programming with Bit Manipulation
Time Complexity: O(n^2) per test case, where n is the length of the string
Space Complexity: O(n) for the dp arrays and auxiliary space

The problem involves counting distinct binary strings that can be obtained from a given string 
by applying a specific operation. The operation modifies a substring and removes one character 
based on positions chosen. This solution uses dynamic programming approach to count all possible 
distinct resulting strings.

Key idea:
- The algorithm processes the string in reverse.
- For each '1' encountered, it calculates how many new strings can be formed by
  considering sequences of consecutive zeros following this '1'.
- It maintains a dp array that tracks number of ways to form a string ending at each position,
  and accumulates answer using modular arithmetic to avoid overflow.

The operation is defined such that:
1. Choose a position p (1 ≤ p ≤ |t|).
2. For all i < p, perform t[i] = max(t[i], t[i+1]).
3. Delete t[p].

This effectively merges leftward and deletes the chosen element.
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 1e6 + 10, mod = 998244353;
char c[1001000];
int n;
int dp[1010000], dp2[2001000], all;

void sol() {
  scanf("%s", c + 1);
  n = strlen(c + 1);
  reverse(c + 1, c + n + 1); // Reverse string for easier processing
  for (int i = 0; i <= n; i++)
    dp[i] = 0;
  c[0] = '1', dp[0] = 1, all = 1; // Initialize starting state
  int ans = 0;
  for (int i = 0; i <= n; i++)
    if (c[i] == '1') { // When we encounter a '1'
      int d = i + 1, s = 0;
      while (d <= n && c[d] == '0')
        d++, s++; // Count how many consecutive zeros follow this '1'
      (ans += 1ll * all * (s + 1) % mod) %= mod; // Add contribution to result
      if (!s)
        continue;
      for (int k = 1, z = 0; k <= s; k++)
        (z += dp[k - 1]) %= mod, dp2[k] = z; // Compute prefix sums in dp2
      for (int j = 1; j <= s; j++)
        (dp[j] += dp2[j]) %= mod, (all += dp2[j]) %= mod; // Update dp and all
    }
  printf("%d\n", (ans + mod - 1) % mod);
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--)
    sol();
  return 0;
}


// https://github.com/VaHiX/codeForces/