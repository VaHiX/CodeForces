# Problem: CF 1394 A - Boboniu Chats with Du
# https://codeforces.com/contest/1394/problem/A

"""
Problem: Boboniu Chats with Du

Purpose:
This code solves a problem where Du speaks in a chat group for n days, and each day he makes fun of Boboniu with a certain fun factor. 
If Du speaks on a given day and the fun factor is greater than m (Boboniu's mood), he gets muzzled for d days.
The goal is to find the maximum total fun factor possible by permuting the array a optimally.

Approach:
We use dynamic programming combined with greedy strategy. We split the elements into two groups:
- Elements > M: These are potentially more valuable if we can use them strategically.
- Elements <= M: These are used greedily in the DP to maximize sum before any muzzle effect.

The idea is to evaluate all possible ways of placing the high-value elements (those greater than M) 
in a way that maximizes the benefit of their usage, considering the muzzle constraints.

Time Complexity: O(N log N)
Space Complexity: O(N)

Algorithms/Techniques:
- Greedy sorting
- Dynamic Programming
- Prefix sum optimization
"""

import sys

input = lambda: sys.stdin.readline().rstrip()
N, D, M = map(int, input().split())
A = list(map(int, input().split()))

# Split into two groups
a1, a2 = [], []  # a1: elements <= M, a2: elements > M
for a in A:
    if a > M:
        a2.append(a)
    else:
        a1.append(a)

# Sort both groups in descending order to ensure greedy choice
a1.sort(reverse=True)  # For maximum sum with fewer muzzle effects
a2.sort(reverse=True)

# DP array to store best prefix sum of elements from a1 (<= M)
dp = [0] * (N + 1)
for i in range(N):
    if i < len(a1):
        dp[i + 1] = dp[i] + a1[i]
    else:
        dp[i + 1] = dp[i]

ans, cur = dp[-1], 0  # ans stores max fun so far; cur tracks current sum of high value elements

# Try placing each element from a2 (high value ones) at different positions
for i in range(len(a2)):
    cur += a2[i]  # Add current high value element to running sum
    
    # Calculate how many days are left after this muzzle period
    t = N - (i * (D + 1) + 1)  # index of last valid day considering muzzle effect
    
    if t < 0:
        break
    
    # Update answer: best of current configuration vs. previous best (with prefix sum)
    ans = max(ans, cur + dp[t])

print(ans)


# https://github.com/VaHiX/codeForces/