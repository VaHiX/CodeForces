# Problem: CF 1932 F - Feed Cats
# https://codeforces.com/contest/1932/problem/F

"""
Algorithm: Greedy with Dynamic Programming
Approach:
1. Use a difference array technique to count how many cats are present at each step.
2. For each step, determine the earliest step where a cat could have been fed to avoid conflicts.
3. Use dynamic programming to select steps optimally, ensuring no cat is fed twice.

Time Complexity: O(n + m)
Space Complexity: O(n)

This solution works by:
- Using a sweep line technique to mark the presence of cats.
- Preprocessing the leftmost valid position for each step.
- Applying DP to find the maximum number of cats that can be fed without overeating.
"""

import sys

input = sys.stdin.readline

S = lambda: input().strip()
L = lambda: list(map(int, input().split()))
I = lambda: int(input().strip())
T = lambda: map(int, input().split())

inf = 10**10
t = I()
for _ in range(t):
    n, m = T()
    line = [0] * (n + 2)  # Difference array to mark cat presence
    left = list(range(n + 1))  # For each step, store earliest valid feeding step

    for i in range(m):
        a, b = T()
        line[a] += 1  # Start of cat presence
        line[b + 1] -= 1  # End of cat presence (exclusive)
        left[b] = min(left[b], a)  # Update earliest step for this position

    # Convert difference array to actual count of cats present at each step
    for i in range(1, n + 1):
        line[i] += line[i - 1]

    # Preprocess 'left' array to ensure for each position, it stores
    # the minimum valid start time considering all steps ahead
    for i in range(n - 1, -1, -1):
        left[i] = min(left[i], left[i + 1])

    # Dynamic Programming step
    # dp[i] represents the maximum number of cats that can be fed up to step i
    dp = [0] * (n + 1)
    for i in range(1, n + 1):
        # Either:
        # 1. Don't feed any cat at step i -> dp[i-1]
        # 2. Feed cats at step i, but only those that haven't been fed before -> dp[left[i]-1] + line[i]
        dp[i] = max(dp[left[i] - 1] + line[i], dp[i - 1])

    print(dp[-1])  # Output the maximum number of cats that can be fed


# https://github.com/VaHiX/CodeForces/