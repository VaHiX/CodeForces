# Problem: CF 2135 A - Against the Difference
# https://codeforces.com/contest/2135/problem/A

"""
Algorithm: Dynamic Programming with Segment Tracking
Technique: 
  - Use dynamic programming where dp[i] represents the length of the longest neat subsequence 
    in the first i elements of the array.
  - For each element x at position i, we maintain a list of previous positions where x appeared.
  - If x has appeared at least x times before, then we can form a block of x elements ending at i.
    We update dp[i+1] by considering the maximum value from dp[previous_x_positions[-x]] + x.

Time Complexity: O(n^2) in worst case due to possible repeated lookups in pos arrays; however,
                 with proper data structures it can be optimized to O(n) average case.
Space Complexity: O(n) for storing dp array and position lists.

This solution processes each element and checks if a valid block of size equal to the element's value
can be formed using previously seen elements.
"""

import sys

input = lambda: sys.stdin.readline().rstrip()
ii = lambda: int(input())
mii = lambda: map(int, input().split())
lii = lambda: list(mii())


def solve():
    n = ii()
    arr = lii()
    dp = [0] * (n + 1)  # dp[i] stores max length of neat subsequence in first i elements
    pos = [[] for _ in range(n + 1)]  # pos[x] stores all indices where x has occurred
    
    for i, x in enumerate(arr):
        dp[i + 1] = dp[i]  # By default, carry forward previous result
        p = pos[x]         # Get list of positions where x was seen
        p.append(i)        # Add current index to the list
        
        # If we've seen x at least x times before, a block of size x can end at this position
        if len(p) >= x:
            dp[i + 1] = max(dp[i + 1], dp[p[-x]] + x)  # Update with block contribution
    return dp[n]


for _ in range(ii()):
    print(solve())


# https://github.com/VaHiX/codeForces/