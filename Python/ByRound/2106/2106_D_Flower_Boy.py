# Problem: CF 2106 D - Flower Boy
# https://codeforces.com/contest/2106/problem/D

"""
D. Flower Boy

Problem Summary:
Igor wants to collect exactly m flowers from a garden of n flowers, where each selected flower must meet a minimum beauty requirement b_i for the i-th flower chosen (from left to right). Before starting, Igor can place one new flower with beauty k anywhere in the garden (once only). The goal is to find the minimum value of k needed to make it possible to collect the required flowers. If already possible without adding a flower, return 0; if impossible even with one flower, return -1.

Algorithms/Techniques:
- Preprocessing using prefix and suffix arrays.
- Binary search or direct checking for valid placements.
- Two-pointer technique to compute valid ranges efficiently.

Time Complexity: O(n + m) per test case, due to linear scan through A and B once for pre/suf arrays and then one more scan to check best k.
Space Complexity: O(m), for storing prefix and suffix arrays of size m+1.

"""

import sys

input = lambda: sys.stdin.readline().rstrip()
ii = lambda: int(input())
mii = lambda: map(int, input().split())
lii = lambda: list(mii())
inf = 1 << 30


def solve():
    n, m = mii()  # Read number of flowers and flowers to collect
    A = lii()     # Beauty values of existing flowers
    B = lii()     # Minimum beauty required for each collected flower

    # Precompute prefix array: pre[i] is the index of first flower >= B[i] in A
    pre = [-1] * (m + 1)
    j = 0  # Pointer for array A
    for i in range(m):
        while j < n and A[j] < B[i]:
            j += 1  # Skip all flowers with beauty less than required
        pre[i + 1] = j
        if j < n:
            j += 1  # Move to next flower after selected one

    # If we couldn't find enough flowers, impossible without adding a new flower
    if pre[-1] < n:
        return 0  # Already all flowers collected, no need for extra

    # Precompute suffix array: suf[i] is the index of last flower >= B[i] in A
    suf = [n] * (m + 1)
    j = n - 1  # Pointer starting from end of A
    for i in range(m - 1, -1, -1):
        while j >= 0 and A[j] < B[i]:
            j -= 1
        suf[i] = j
        if j >= 0:
            j -= 1

    # Find minimum k such that we can select valid m flowers
    ans = inf
    for i in range(m):
        # Check whether there's a gap between what we collected before and after
        # pre[i] is the earliest allowed start point to collect B[i]
        # suf[i+1] is the latest allowed ending point for previous collection
        if pre[i] < suf[i + 1]:  # Valid interval exists
            # The required minimum k to have a flower at this gap
            ans = min(ans, B[i])

    return ans if ans < inf else -1


for _ in range(ii()):
    print(solve())


# https://github.com/VaHiX/codeForces/