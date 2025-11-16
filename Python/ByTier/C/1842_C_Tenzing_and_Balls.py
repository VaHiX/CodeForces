# Problem: CF 1842 C - Tenzing and Balls
# https://codeforces.com/contest/1842/problem/C

"""
Algorithm: Dynamic Programming with tracking of last seen positions
Techniques: 
  - Sliding window / greedy approach with DP
  - Efficient tracking of color occurrences using last_seen array
Time Complexity: O(n)
Space Complexity: O(n)

This problem uses dynamic programming to determine the maximum number of balls 
that can be removed by repeatedly erasing contiguous subarrays of same-colored balls.
The key idea is to track for each color the last time it was seen, 
and use DP to compute the maximum removals up to each position.
"""

from sys import stdin

input = stdin.readline


for _ in range(int(input())):
    n = int(input())
    A = list(map(int, input().split()))

    # last_seen[a] stores the latest index where color 'a' was seen
    last_seen = [-(10**15)] * (n + 1)
    # dp[i] stores the maximum number of balls that can be removed from the first i balls
    dp = [0] * (n + 1)
    
    for i, a in enumerate(A):
        # At each position i, we have two choices:
        # 1. Don't remove the current ball: dp[i+1] = dp[i]
        # 2. Remove a subarray ending at position i, starting from some previous position j
        #    This means we remove from j to i (inclusive), where all elements are color a
        #    The total removed is (i - j + 1) = (i - (last_seen[a] + 1) + 1) = i - last_seen[a]
        #    But we want to maximize this, so we consider max so far in dp[i] - i + last_seen[a] + 1
        #    This can be rearranged to dp[i] - i + last_seen[a] + 1 => dp[i] - i + last_seen[a] + 1
        #    So, dp[i+1] = max(dp[i], last_seen[a] + i + 1)
        dp[i + 1] = max(dp[i], last_seen[a] + i + 1)
        # Update last_seen[a] to reflect that we have seen color 'a' at position i
        # The value stored helps determine future removals
        last_seen[a] = max(last_seen[a], dp[i] - i)

    print(dp[-1])


# https://github.com/VaHiX/CodeForces/