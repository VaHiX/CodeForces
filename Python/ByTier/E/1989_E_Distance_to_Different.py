# Problem: CF 1989 E - Distance to Different
# https://codeforces.com/contest/1989/problem/E

"""
Code Purpose:
This code solves the problem of counting the number of distinct arrays b that can be derived from all possible arrays a, where:
- a is an array of n integers, each from 1 to k.
- Each integer from 1 to k appears at least once in a.
- b[i] is the minimum distance from index i to the closest element in a that is different from a[i].

The approach uses dynamic programming (DP) with states representing how many distinct values have been placed at each index,
and tracks cumulative sums to efficiently compute transitions.

Algorithms/Techniques:
- Dynamic Programming with rolling sum optimization
- Modular arithmetic for large results
- State compression based on number of distinct values used

Time Complexity: O(n * k)
Space Complexity: O(n * k)
"""

import sys


class Solution:
    def solve(self, n, k):
        mod = 998244353
        # dp[i][j]: number of ways to form prefix of length i using exactly j distinct values
        dp = [[0] * (k + 1) for _ in range(n + 1)]
        dp[0][0] = 1  # Base case: 0-length prefix with 0 distinct values
        sum_dp = [0] * (k + 1)
        sum_dp[0] = 1  # Cumulative sum of dp[0][*]
        
        for i in range(1, n + 1):
            # Traverse in reverse to prevent using updated values in same iteration
            for j in range(k, -1, -1):
                nj = min(j + 1, k)  # Next number of distinct values
                # Add the contribution from previous state
                dp[i][nj] += sum_dp[j]
                # Subtract the contribution that goes out of window (for i > 2 and i != n)
                if i > 2 and i != n:
                    dp[i][nj] -= dp[i - 2][j]
                dp[i][nj] %= mod
            
            # Update cumulative sum for next iteration
            for j in range(k + 1):
                sum_dp[j] += dp[i][j]
                sum_dp[j] %= mod
                
        # Return the total number of ways to finish the array with exactly k distinct values
        return (dp[n][k] % mod + mod) % mod


input = sys.stdin.read().strip().split()
n = int(input[0])
k = int(input[1])
solution = Solution()
result = solution.solve(n, k)
print(result)


# https://github.com/VaHiX/CodeForces/