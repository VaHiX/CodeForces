// Problem: CF 1750 F - Majority
// https://codeforces.com/contest/1750/problem/F

/*
Algorithm: Dynamic Programming with Prefix Sums
Approach:
  - We define dp[i] as the number of rated binary strings of length i.
  - The recurrence relation is built upon the idea that we can extend a valid string of length j 
    to a longer string of length i by adding a suffix such that the electricity spread operation
    is valid.
  - sum array is used to maintain prefix sums of dp for efficient computation.
  - Using the property that an operation is valid if 2 * (number of 1s) >= length of segment,
    we compute transitions by considering all possible valid segments [i, j].

Time Complexity: O(n^2)
Space Complexity: O(n)
*/

#include <iostream>

using namespace std;
int n, m;
long long dp[5005], sum[10005], pw[5005];
int main() {
  cin >> n >> m;
  dp[1] = pw[0] = sum[2] = 1;
  for (int i = 1; i <= n; i++)
    pw[i] = pw[i - 1] * 2 % m;  // Precompute powers of 2 modulo m
  for (int i = 2; i <= n; i++) {
    (sum[i] += sum[i - 1]) %= m, dp[i] = pw[i - 2];  // Initialize dp[i] and update sum
    for (int j = 1; (j + 1) * 2 < i; j++) {
      long long tmp = sum[i - 2 * j - 1] * dp[j] % m;  // Compute temporary value for transition
      (dp[i] += m - tmp) %= m, (sum[i + j] += tmp) %= m;  // Update dp[i] and sum
    }
    (sum[i + i] += dp[i]) %= m;  // Update sum for later use
  }
  cout << dp[n] << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/