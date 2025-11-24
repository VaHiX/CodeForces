# Problem: CF 2133 D - Chicken Jockey
# https://codeforces.com/contest/2133/problem/D

"""
D. Chicken Jockey
Algorithms/Techniques: Dynamic Programming
Time Complexity: O(n)
Space Complexity: O(n)

The problem involves determining the minimum number of attacks required to eliminate all mobs in a stack.
Each mob can be attacked, and if it dies, mobs above it fall down and take fall damage equal to their position 
in the previous stack. The process continues recursively.
This solution uses dynamic programming where dp[i] represents the minimal number of attacks needed to clear
all mobs up to index i (0-indexed), assuming the stack is intact at that point.

Key idea:
- We simulate the process with a DP transition.
- At each step, we decide whether it's more optimal to attack the current mob or to continue building up the stack.
"""

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    # dp[j] stores the minimum number of attacks needed to eliminate mobs up to index j-1
    dp = [(0 if j != 1 else a[0]) for j in range(n + 1)]
    for j in range(1, n):
        # Transition: either attack current mob or attack previous mob to let it fall and cause damage
        dp[j + 1] = min(dp[j] + a[j] - 1, dp[j - 1] + a[j - 1] + max(0, a[j] - j))
    print(dp[-1])


# https://github.com/VaHiX/codeForces/