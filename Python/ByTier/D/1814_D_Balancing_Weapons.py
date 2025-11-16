# Problem: CF 1814 D - Balancing Weapons
# https://codeforces.com/contest/1814/problem/D

"""
Algorithm: Two Pointers with Set-based Range Checking
Time Complexity: O(n^2 * log(n)) in worst case due to nested loops and set operations
Space Complexity: O(n) for storing fire rates and auxiliary arrays

This solution uses a two-pointer technique over the sorted firepower values to find the maximum number of guns that can be kept unchanged while achieving balance. For each valid range of firepower, we check if all fire rates can be satisfied by integer damage values within that range using set operations.
"""

import sys

input = sys.stdin.buffer.readline

t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    f = list(map(int, input().split()))
    d = list(map(int, input().split()))
    p = [f[i] * d[i] for i in range(n)]
    p.sort()
    s = set()
    for fi in f:
        if fi > k:
            s.add(fi)

    def check(a, b):
        # If the range exceeds allowed difference k, impossible to balance
        if b - a > k:
            return 0
        # Determine the range of possible damage values
        st = max(b - k, 1)
        en = a + k
        # Precompute how many fire rates can be satisfied for each damage value
        x = [0 for _ in range(en - st + 1 + 1)]
        for si in s:
            # Compute the first valid damage value for fire rate si under the constraint
            v = ((st + si - 1) // si) * si
            while v <= en:
                x[v - st] += 1
                v += si
        c = 0
        # Check if there exists any valid damage assignment for all fire rates
        for i in range(st, st + k + 1):
            c += x[i - st]
        # Sliding window to validate all ranges of size k+1
        for i in range(st, a + 1):
            if c == len(s):
                return 1
            c -= x[i - st]
            c += x[i - st + k + 1]
        return 0

    result = 0
    a = 0
    b = 0
    # Two pointers to find maximum size valid contiguous subarray
    while a < n and b < n:
        if check(p[a], p[b]):
            result = max(result, b - a + 1)
            b += 1
        else:
            a += 1
            if a > b:
                b = a
    print(n - result)


# https://github.com/VaHiX/CodeForces/