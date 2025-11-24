# Problem: CF 2006 D - Iris and Adjacent Products
# https://codeforces.com/contest/2006/problem/D

"""
Algorithm: Segment Tree + Square Root Decomposition + Two Pointers
Time Complexity: O(n * sqrt(k) + q * sqrt(k) * log(q))
Space Complexity: O(n + q)

Approach:
- For each query, we process subarray [l, r] by decomposing the problem into blocks of size sqrt(k)
- Preprocessing involves adjusting values in array b such that all elements are <= sqrt(k)
- We use a sliding window technique with two pointers to count valid pairs
- A frequency array is used to track how many times each element appears in the current window
- For each window, we compute minimum operations to make product of adjacent elements <= k
- Queries are sorted to optimize processing order

This solution leverages block decomposition and square root optimization for efficient querying.
"""

import io
import math
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v, w):
    return u << 40 ^ v << 20 ^ w


t = int(input())
ans = []
for _ in range(t):
    n, q, k = map(int, input().split())
    b = [0] + list(map(int, input().split()))
    m = int(math.sqrt(k))
    # Adjust values in b to be within sqrt(k) range, or compute reciprocal value
    for i in range(1, n + 1):
        if b[i] > m:
            b[i] = k // b[i] + m  # Use reciprocal to avoid large numbers
    l0, r0, q0 = [0] * q, [0] * q, [0] * q
    m1 = 357  # Block size for decomposition
    for i in range(q):
        l, r = map(int, input().split())
        l1 = (l - 1) // m1  # Compute block number for left boundary
        r1 = r if not l1 & 1 else n - r  # Modify right boundary based on even/odd
        l0[i], r0[i], q0[i] = l, r, f(l1, r1, i)  # Encode query info
    l, r = 1, 0  # Sliding window pointers
    cnt = [0] * (2 * m + 1)  # Frequency array for counting elements
    ans0, q0 = [0] * q, [i & 0xFFFFF for i in sorted(q0)]  # Sort queries based on encoded info
    for i in q0:
        l1, r1 = l0[i], r0[i]  # Get current query boundaries
        # Adjust window from left
        while l1 < l:
            l -= 1
            cnt[b[l]] += 1
        # Adjust window from right
        while r < r1:
            r += 1
            cnt[b[r]] += 1
        # Shrink window from left
        while l < l1:
            cnt[b[l]] -= 1
            l += 1
        # Shrink window from right
        while r1 < r:
            cnt[b[r]] -= 1
            r -= 1
        u, v, ans1 = 0, 0, 0  # Variables to count operations
        # Process elements in frequency array to calculate minimal operations
        for j in range(1, m + 1):
            c = max((v - u + cnt[j + m] - cnt[j] + 1) >> 1, 0)  # Compute needed changes
            ans1 += c
            u += cnt[j] + c
            v += cnt[j + m] - c
            if u + v == r - l + 1:  # If all elements are covered
                if u > v and c:  # Handle tie-breaking
                    ans1 -= 1
                break
        ans0[i] = ans1
    ans.append(" ".join(map(str, ans0)))
sys.stdout.write("\n".join(ans))


# https://github.com/VaHiX/CodeForces/