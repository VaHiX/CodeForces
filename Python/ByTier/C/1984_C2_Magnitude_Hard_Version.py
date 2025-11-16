# Problem: CF 1984 C2 - Magnitude (Hard Version)
# https://codeforces.com/contest/1984/problem/C2

"""
Algorithm: Dynamic Programming with State Tracking
Purpose: Count the number of ways to choose between two operations at each step to maximize the final value of c.
Time Complexity: O(n) per test case, where n is the length of the array
Space Complexity: O(1) - only using a few variables to track states

The approach tracks:
- mx: maximum value of c so far (as if we always took option 1)
- mi: minimum value of c so far (as if we always took option 1)
- mxc: number of ways to achieve the maximum value
- mic: number of ways to achieve the minimum value

At each step, we decide whether to take absolute value or not, updating both the max and min values and their counts accordingly.
"""

import sys

input = sys.stdin.buffer.readline
p = 998244353
for _ in range(int(input())):
    n = int(input())
    mx, mi = 0, 0
    mxc, mic = 1, 0
    for x in map(int, input().split()):
        # Calculate new maximum value (either by adding directly or taking absolute)
        mx2 = max(mx + x, abs(mi + x))
        # Update count of ways to reach new maximum
        mxc2 = (int(mx + x == mx2) + int(abs(mx + x) == mx2)) * mxc + (
            int(mi + x == mx2) + int(abs(mi + x) == mx2)
        ) * mic
        # Update minimum value by adding current element
        mi += x
        # Update count of ways to reach new minimum
        mic2 = (1 + int(mi >= 0)) * mic + int(mx + x == mi != mx2) * mxc
        # Update mx and mxc for next iteration
        mx = mx2
        mxc, mic = mxc2 % p, mic2 % p
    print(mxc)


# https://github.com/VaHiX/CodeForces/