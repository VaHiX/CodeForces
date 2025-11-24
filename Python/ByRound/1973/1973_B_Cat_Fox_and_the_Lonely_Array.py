# Problem: CF 1973 B - Cat, Fox and the Lonely Array
# https://codeforces.com/contest/1973/problem/B

"""
Purpose: 
    This code finds the "loneliness" of an array, defined as the smallest positive integer k such that 
    all consecutive subarrays of length k have the same bitwise OR value.

Algorithms/Techniques:
    - For each bit position (0 to 19), we track the maximum gap between indices where that bit is set.
    - The loneliness k is the maximum of these gaps across all bit positions.
    - This works because if two subarrays of length k have the same OR, then for each bit position, 
      the bits must remain consistent across the subarray — i.e., no new bits are set in the middle.

Time Complexity: O(20 * n) = O(n)
Space Complexity: O(1) - only using a few variables regardless of input size.
"""

import sys

input = sys.stdin.readline


def solve():
    n = int(input())
    A = list(map(int, input().split()))

    ans = 1
    # Iterate over each bit position (0 to 19, since max value < 2^20)
    for j in range(20):
        last = -1  # Position of the last element with bit j set
        curr = 1   # Current maximum gap between elements with bit j set
        for i, a in enumerate(A):
            # If the j-th bit is set in a
            if a >> j & 1:
                # Update current max gap
                curr = max(curr, i - last)
                last = i  # Update last position with bit j set
        # If there was at least one element with bit j set
        if last == -1:
            continue
        # Check gap from last set bit to end of array
        curr = max(curr, n - last)
        # Update the overall answer with maximum gap found so far
        ans = max(ans, curr)

    return ans


T = int(input())
out = [solve() for _ in range(T)]
print("\n".join(map(str, out)))


# https://github.com/VaHiX/CodeForces/