# Problem: CF 1741 E - Sending a Sequence Over the Network
# https://codeforces.com/contest/1741/problem/E

"""
Algorithm: Dynamic Programming
Purpose: Determine if a given sequence b could be obtained by sending a sequence a over the network.
         Each segment's length is placed either before or after the segment in the final sequence.

Time Complexity: O(n), where n is the length of the sequence b.
Space Complexity: O(n), for the dp array of size n+1.

The approach uses dynamic programming:
- dp[i] represents whether it's possible to form a valid sequence up to position i.
- For each position i in b:
  - If b[i] is a segment length and we can reach position i from a previous valid position,
    we mark dp[i+1] = True.
  - If we are at a position and b[i] represents a segment length, we can extend the segment
    to position i + b[i] + 1.
"""

for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    dp = [False] * (n + 1)
    dp[0] = True
    for i in range(n):
        # If we can come from a previous position such that the segment length matches
        if i - a[i] >= 0 and dp[i - a[i]]:
            dp[i + 1] = True
        # If we are at the start of a segment and can extend it
        if i + a[i] + 1 <= n and dp[i]:
            dp[i + a[i] + 1] = True
    print(["NO", "YES"][dp[-1]])


# https://github.com/VaHiX/CodeForces/