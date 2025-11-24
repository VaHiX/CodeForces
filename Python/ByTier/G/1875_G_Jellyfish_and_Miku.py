# Problem: CF 1875 G - Jellyfish and Miku
# https://codeforces.com/contest/1875/problem/G

"""
Code Purpose:
This code solves the problem of finding the minimum expected number of days for Jellyfish to reach city n from city 0,
by optimally assigning beauty values to roads under a budget constraint. The solution uses dynamic programming with
a specific transition based on expected hit times for random walks on a path graph.

Algorithms/Techniques:
- Dynamic Programming (DP)
- Mathematical expectation calculation for random walks
- Optimization with budget constraint

Time Complexity: O(n * m^2)
Space Complexity: O(m)

The problem models a random walk on a path graph where each node has edges with certain beauty values. 
We use DP where dp[i] represents the minimum expected number of steps to reach the end from the current state,
with the constraint that the total sum of beauty values is at most m.
"""

def MII():
    return map(int, input().split())

n, m = MII()

inf = float('inf')

# Initialize DP array where dp[i] represents the minimum expected steps with sum of beauties = i
dp = [inf] * (m + 1)
dp[0] = 0

# Iterate through each road
for i in range(n):
    # Create new DP array for next iteration
    ndp = [inf] * (m + 1)
    for j in range(m + 1):
        if dp[j] < inf:
            # Try all possible values for current road's beauty
            for k in range(1, m // (n - i) + 1):
                if j + k > m:
                    break
                # Update the DP state with new expected number of steps
                if dp[j] + j / k < ndp[j + k]:
                    ndp[j + k] = dp[j] + j / k
    dp = ndp

# Final answer is n plus twice the expected number of steps (as per the formula derived from the problem)
print(n + dp[-1] * 2)


# https://github.com/VaHiX/CodeForces/