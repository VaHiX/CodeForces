# Problem: CF 2153 F - Odd Queries on Odd Array
# https://codeforces.com/contest/2153/problem/F

"""
F. Odd Queries on Odd Array

Purpose:
This code handles queries on a cute array to compute the "beauty" of subarrays.
The beauty is defined as the sum of distinct values that appear an odd number of times in the subarray.

Algorithms/Techniques:
1. Preprocessing using sparse table for range minimum queries (RMQ)
2. Segment tree-like preprocessing with prefix sums for efficient range queries
3. Binary search (bisect) for finding positions in sorted arrays
4. Efficiently calculating query results leveraging precomputed data structures

Time Complexity: O((n + q) * log n)
Space Complexity: O(n * log n)

"""

import bisect

t = int(input())
for _ in " " * t:
    n, q = map(int, input().split())
    (*a,) = map(int, input().split())
    v = [[] for _ in range(n + 1)]
    for i, x in enumerate(a):
        v[x].append(i)
    s1 = [0] * (n + 1)
    s2 = [0] * (n + 1)
    for x in range(1, n + 1):
        p = v[x]
        if not p:
            continue
        k = len(p)
        for i in range(k):
            s1[p[i] + 1] += x if i % 2 == 0 else -x # Accumulate positive/negative contribution based on parity of index in list
            s2[p[k - 1 - i] + 1] += x if i % 2 == 0 else -x # Same as above but from reverse
    for i in range(1, n + 1):
        s1[i] += s1[i - 1]
        s2[i] += s2[i - 1]
    f = [v[a[i]][0] for i in range(n)] # f contains first occurrence of each element
    lg = (n).bit_length() # Ceiling of log2(n) used to compute sparse table size
    st = [f[:]] # Sparse table initialized with base level
    for k in range(1, lg):
        p = st[-1]
        m = n - (1 << k) + 1 # Length of current segment for level k
        c = [0] * m
        h = 1 << (k - 1)
        for i in range(m):
            x = p[i]
            y = p[i + h]
            c[i] = x if x < y else y # RMQ: take minimum of two segments
        st.append(c)
    g = [0] * (n + 1)
    for i in range(2, n + 1):
        g[i] = g[i >> 1] + 1 # Precalculate log base 2 values

    def rmq(l, r):
        k = g[r - l]
        return min(st[k][l], st[k][r - (1 << k)]) # Range minimum query in O(1)

    pref = [0] * (n + 1)
    for i in range(1, n + 1):
        pref[i] = pref[i - 1] + a[i - 1] # Prefix sum array for quick subarray sum
    ans = 0
    res = []
    for _ in range(q):
        x, y = map(int, input().split())
        l = (x - 1 + ans) % n # Decode query with previous answer
        r = (y - 1 + ans) % n
        if l > r:
            l, r = r, l
        r += 1
        z = rmq(l, r) # Find index of minimum element in the range [l, r)
        val = a[z]
        cur = s2[z] - s2[l] + s1[r] - s1[z] # Compute current contribution
        P = v[val] # All positions where value val appears
        L = bisect.bisect_left(P, l) # Find first position >= l
        M = bisect.bisect_left(P, z) # Find first position >= z
        R = bisect.bisect_left(P, r) # Find first position >= r
        if (M - L) & 1: # If there is an odd count of val in [l,z)
            cur -= val if ((len(P) - M) % 2 == 0) else -val # Adjust for parity correction
        if (R - M) & 1: # If there is an odd count of val in (z,r]
            cur -= val if (M % 2 == 0) else -val # Adjust for parity correction
        cur += ((R - L) & 1) * val # Add contribution if total count is odd
        res.append(str(cur))
        ans = cur
    print(" ".join(res))


# https://github.com/VaHiX/CodeForces/