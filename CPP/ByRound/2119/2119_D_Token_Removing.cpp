// Problem: CF 2119 D - Token Removing
// https://codeforces.com/contest/2119/problem/D

/*
D. Token Removing
Algorithms/Techniques: Dynamic Programming, Combination Math

Time Complexity: O(n^2)
Space Complexity: O(n^2)

The problem involves computing the sum of weights over all valid sequences of length n,
where each sequence satisfies a_i <= i for all i. The weight f(a) represents the number
of ways to remove tokens based on the sequence.

We use dynamic programming to calculate:
- dp[i][j] = number of ways to place j tokens in the first i operations.
- The recurrence relation builds on previous states considering how many tokens can be removed at each step.

For each test case, we compute the total sum of weights for all (n+1)! valid sequences modulo m.
*/

#include <iostream>

using namespace std;
int n, m, t;
long long dp[5005][5005], ans;

int main() {
  cin >> t;
  while (t--) {
    cin >> n >> m;
    ans = 0;
    // Initialize the dp array to zero
    for (int i = 0; i <= n; i++)
      for (int j = 0; j <= i; j++)
        dp[i][j] = 0;
    dp[0][0] = 1; // Base case: one way to place 0 tokens in 0 operations
    
    // Fill the DP table using recurrence relation
    for (int i = 1; i <= n; i++)
      for (int j = 0; j <= i; j++)
        dp[i][j] =
            (dp[i - 1][j - 1] + (n - i + 1) * (j + 1) * dp[i - 1][j]) % m;
    
    // Sum all values in the last row to get the final answer
    for (int i = 0; i <= n; i++)
      ans = (ans + dp[n][i]) % m;
    cout << ans << endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/