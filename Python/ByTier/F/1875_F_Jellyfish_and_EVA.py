# Problem: CF 1875 F - Jellyfish and EVA
# https://codeforces.com/contest/1875/problem/F

"""
Algorithm: Dynamic Programming with Optimal Choice Strategy
Approach:
- This problem models a game between Jellyfish and Asuka on a directed acyclic graph (DAG).
- For each city, we compute the maximum probability of reaching the final city (n) when both players play optimally.
- Jellyfish chooses a road optimally to maximize success probability.
- Asuka chooses a road uniformly at random (unknown to Jellyfish).
- The probability calculation is based on the number of roads from each city and optimal selection strategy using dynamic programming.

Time Complexity: O(n^2 + m)
- Building adjacency list: O(m)
- Computing probabilities matrix p: O(n^2)
- DP computation: O(n^2) in worst case due to sorting and nested loops

Space Complexity: O(n^2 + n)
- Probability matrix p: O(n^2)
- DP array: O(n)
- Adjacency list: O(m)
"""

import random
import sys

input = sys.stdin.readline
rd = random.randint(10**9, 2 * 10**9)

t = int(input())
for _ in range(t):
    n, m = map(int, input().split())
    g = [[] for _ in range(n)]
    for i in range(m):
        u, v = map(int, input().split())
        g[u - 1].append(v - 1)
    p = [[0] * (n + 1) for _ in range(n + 1)]
    for k in range(1, n + 1):
        p[k][1] = 1 / k
        for i in range(2, k + 1):
            # Recurrence relation for probability calculation
            # p[k][i] is the probability that in k roads, the i-th best choice leads to success
            p[k][i] = p[k - 2][i - 2] * (i - 2) / k + p[k - 2][i - 1] * (k - i) / k
    dp = [0] * n
    dp[-1] = 1  # Base case: probability of reaching destination from destination is 1
    for i in range(n - 2, -1, -1):
        # Sort cities by their DP values in descending order to prioritize better choices
        g[i].sort(key=lambda x: -dp[x])
        for j in range(len(g[i])):
            # Accumulate probability using the recurrence relation
            dp[i] += dp[g[i][j]] * p[len(g[i])][j + 1]
    print(dp[0])


# https://github.com/VaHiX/CodeForces/