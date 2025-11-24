# Problem: CF 2118 F - Shifts and Swaps
# https://codeforces.com/contest/2118/problem/F

"""
F. Shifts and Swaps

Purpose:
This code determines whether one array can be transformed into another using two types of operations:
1. Cyclic left shift of the array.
2. Swap two adjacent elements if their difference is at least 2.

Algorithm:
The solution uses a hash-based approach to represent the structure of arrays and compare them.
It computes hashes for each element's position based on a rolling hash technique,
and checks all possible rotations of one array against the other.

Time Complexity:
O(n * m * log(n)) per test case due to binary search over buckets and rolling hash computations.

Space Complexity:
O(n + m) for storing the arrays, hash values, and buckets.
"""

import random

MOD = -1 + (1 << 61)
baku = []
for _ in range(int(input())):
    n, m = [int(t) for t in input().split()]
    l1 = [int(t) - 1 for t in input().split()]
    l2 = [int(t) - 1 for t in input().split()]
    BASE = random.randint(1, MOD - 1)
    HASHES = [random.randint(1, MOD - 1) for _ in range(m)]

    def hash(a):
        h = [1] * n
        bins = [[] for _ in range(m)]
        # Populate buckets for each element type
        for i in range(n):
            bins[a[i]].append(i)
        # Also store indices with offset n to handle cyclic shifts
        for i in range(n):
            bins[a[i]].append(i + n)
        # Compute rolling hashes per bucket
        for j in range(1, m):
            b1, b2 = bins[j - 1], bins[j]
            for z in range(len(b2) // 2):
                i = -1
                jump = 1 << 20
                while jump:
                    if i + jump < len(b1) and b1[i + jump] < b2[z]:
                        i += jump
                    jump //= 2
                i += 1
                p = 1
                acc = HASHES[j]
                # Rolling hash computation within the window
                while i < len(b1) and b1[i] < b2[z + 1]:
                    p += acc * h[b1[i] % n]
                    acc = acc * HASHES[j] % MOD
                    i += 1
                h[b2[z]] = p % MOD
        # Extract final hashes from last bucket
        fin = [h[i] for i in bins[m - 1] if i < n]
        p = 0
        acc = 1
        # Hash combination of all final elements with base
        for e in fin:
            p += e * acc
            acc = acc * BASE % MOD
        p %= MOD
        best = (p, 0)
        down = pow(BASE, -1, MOD)
        up = pow(BASE, len(fin) - 1, MOD)
        # Try all rotations and find minimum hash value
        for i in range(len(fin)):
            best = min(best, (p, i))
            e = fin[i]
            p = (e * up + (p - e) * down) % MOD
        i = best[1]
        return fin[i:] + fin[:i]

    baku.append("YES" if hash(l1) == hash(l2) else "NO")
print(*baku)


# https://github.com/VaHiX/codeForces/