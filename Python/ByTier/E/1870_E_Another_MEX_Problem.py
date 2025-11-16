# Problem: CF 1870 E - Another MEX Problem
# https://codeforces.com/contest/1870/problem/E

"""
Algorithm: Dynamic Programming with MEX tracking and XOR optimization
Time Complexity: O(n^2)
Space Complexity: O(n^2)

This solution uses a dynamic programming approach to compute the maximum XOR 
of MEX values from non-overlapping subarrays. 

The key idea is to track for each position the set of possible XOR values 
that can be obtained, using a rolling approach where we maintain:
1. MEX values for subarrays ending at current position
2. A counter to track which XOR values are achievable
3. Efficient updates to maintain the set of valid XORs

For each element, we calculate the MEX of subarrays ending at that element and 
update the set of achievable XOR values by combining with previous results.
"""

import math
import sys
from collections import *

input = lambda: sys.stdin.readline().rstrip()
sint = lambda: int(input())
mint = lambda: map(int, input().split())
ints = lambda: list(map(int, input().split()))


def solve() -> None:
    n = sint()
    nums = [math.inf] + ints()  # Add sentinel value at beginning
    ok = Counter()
    ok[0] = 1  # Initially, XOR value 0 is achievable
    mex = [0]  # Array to store MEX values for subarrays
    s = [0] * (n + 5)  # Prefix sum-like array for indexing
    s[1] = 1  # Initialize base case
    u = [0] * (n + 5)  # Track last occurrence of values
    y = [0] * (n + 5)  # Track minimum index for each MEX
    for r in range(1, n + 1):
        m, z = 0, []  # m: current MEX, z: new XOR values to add
        for l in range(r, 0, -1):  # Check all subarrays ending at r
            u[nums[l]] = r  # Mark last occurrence of nums[l]
            # While the current value `m` has no occurrence in current subarray
            while u[m] == r:
                m += 1
            # Skip if this MEX has been processed for this starting position
            if y[m] >= l:
                continue
            # Process previous XOR values and combine them with new MEX
            for i in range(s[y[m]], s[l]):
                v = m ^ mex[i]  # XOR of current MEX with previous values
                if not ok[v]:  # If this XOR hasn't been seen yet
                    ok[v] = 1  # Mark as achievable
                    z.append(v)  # Add to list of new values
            y[m] = l  # Update the minimum start index for MEX m
        # Update the mex array with new XOR values
        for i in z:
            mex.append(i)
        s[r + 1] = len(mex)  # Update prefix sum for new length
    # Find maximum achievable XOR value
    for x in range(n, -1, -1):
        if ok[x]:
            print(x)
            return


for _ in range(sint()):
    solve()


# https://github.com/VaHiX/CodeForces/