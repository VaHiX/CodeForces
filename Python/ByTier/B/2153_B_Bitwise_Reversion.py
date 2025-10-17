# Problem: CF 2153 B - Bitwise Reversion
# https://codeforces.com/contest/2153/problem/B

# ====================================================================
# Problem: Bitwise Reversion
# Description: Determine if there exist three non-negative integers a, b, c
#              such that a & b = x, b & c = y, a & c = z.
# Algorithm:
#   - For each bit position, we check whether the given constraints are consistent.
#   - Let's define:
#     - ab = a & b
#     - bc = b & c  
#     - ac = a & c
#   - For any bit position, if ab, bc, ac are all 1, then all of a,b,c must be 1 at that bit.
#   - If exactly one of them is 1, then exactly one of the corresponding a,b,c is 1 and the others are not.
#   - If exactly two are 1, such as ab=1, bc=1, ac=0, then this is impossible because if a&b=1 and b&c=1,
#     then b must be 1, so a&c should also be 1 since both are 1.
#   - Hence, the necessary and sufficient condition is that (x & y) == (y & z) == (z & x).
#
# Time Complexity: O(1) per test case
# Space Complexity: O(1)
# ====================================================================

import sys

input = sys.stdin.readline
t = int(input())
for _ in range(t):
    x, y, z = list(map(int, input().split()))
    # Check consistency condition for the bitwise AND values
    if (x & y) == (y & z) == (z & x):
        print("YES")
    else:
        print("NO")


# https://github.com/VaHiX/CodeForces/