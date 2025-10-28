# Problem: CF 2119 C - A Good Problem
# https://codeforces.com/contest/2119/problem/C

"""
C. A Good Problem

Purpose:
This code solves a problem where we need to find the k-th element of the lexicographically smallest array of length n, such that:
1. All elements are in range [l, r]
2. The bitwise AND of all elements equals the bitwise XOR of all elements.
3. If no such array exists, return -1.

Approach:
- Special cases for n=1 and n=2 are handled directly.
- For larger n, we attempt to construct a valid array with minimal lexicographical order.
  We use bit manipulation tricks to determine if the required condition can be satisfied.
- The value of x = 1 << l.bit_length() is computed to find a suitable candidate.
  If x > r, it means no valid number in range can satisfy constraints.
  Otherwise, based on k and n, we return either l or x.

Time Complexity: O(1) per test case
Space Complexity: O(1)
"""

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n, l, r, k = map(int, input().split())
    if n & 1:  # If n is odd
        print(l)  # For odd n, we can always use l as the answer
        continue
    if n == 2:  # If n == 2, no valid array exists
        print(-1)
        continue
    x = 1 << l.bit_length()  # Compute next power of 2 greater than or equal to l
    if x > r:  # If this power of 2 is beyond the allowed range
        print(-1)
    else:
        print(l if k <= n - 2 else x)  # Use l if k is small enough, otherwise use x


# https://github.com/VaHiX/codeForces/