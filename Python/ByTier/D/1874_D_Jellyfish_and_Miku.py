# Problem: CF 1874 D - Jellyfish and Miku
# https://codeforces.com/contest/1874/problem/D

"""
Algorithm: Dynamic Programming
Purpose: To find the minimum expected number of days Jellyfish takes to reach city n from city 0,
         given constraints on road beauty sums.

The problem involves finding optimal beauty values for roads such that the expected time to reach city n is minimized,
subject to the constraint that the sum of all beauties does not exceed m.

We use dynamic programming where:
- dp[i] represents the minimum expected time to reach city n using a total beauty sum of i.
- For each step (from n down to 1), we compute new dp values based on previous ones.
- For a given number of roads yet to be assigned (N - n + 1), we iterate over possible beauty values x.
- Transition formula: dp[m+x] = min(dp[m+x], prev[m] + m/x)

Time Complexity: O(N * M^2)
Space Complexity: O(M)
"""

N, M = map(int, input().split())
inf = 1e20
dp = [inf] * (M + 1)
dp[0] = 0
for n in range(1, N + 1):
    prev = dp
    dp = [inf] * (M + 1)
    for m in range(M + 1):
        for x in range(1, M - m + 1):
            if m + x * (N - n + 1) > M:
                break
            dp[m + x] = min(dp[m + x], prev[m] + m / x)
ans = dp[M] * 2 + N
print(ans)


# https://github.com/VaHiX/CodeForces/