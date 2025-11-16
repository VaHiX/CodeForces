# Problem: CF 1736 C2 - Good Subarrays (Hard Version)
# https://codeforces.com/contest/1736/problem/C2

"""
Algorithm: 
This solution uses a sliding window technique combined with precomputed prefix sums to efficiently calculate the number of good subarrays. For each index i, we compute the maximum rightmost position j such that the subarray from i to j is good. Then, we precompute prefix sums to quickly answer range queries. During each query, we adjust the total count based on changes in the array.

Time Complexity: O(n log n + q log n)
Space Complexity: O(n)
"""

import sys

input = sys.stdin.readline
inf = float("inf")


def getInt():
    return int(input())


def getStr():
    return input().strip()


def getList(split=True):
    s = getStr()
    if split:
        s = s.split()
    return map(int, s)


t = 1


def solve():
    n = getInt()
    a = list(getList())
    j = res = 0
    p = [0] * n
    P = [0] * n
    from bisect import bisect_left

    f = {}
    for i, x in enumerate(a):
        j = max(j, i)
        # Find the maximum j such that subarray from i to j is good
        while j < n and a[j] >= j + 1 - i:
            j += 1
        res += j - i  # Add count of good subarrays starting at i
        if j - 1 not in f:
            f[j - 1] = i  # Store leftmost index for this right boundary
            J = j + 1
        # Compute extended boundary for P array
        while J < n and a[J] >= J + 1 - i:
            J += 1
        # Prefix sum for p array
        p[i] = p[i - 1] + j - 1 if i > 0 else j - 1
        # Prefix sum for P array
        P[i] = P[i - 1] + J - j if i > 0 else J - j
    q = getInt()

    def calc(l, r, p):
        # Calculate sum in range [l, r] using prefix sums
        if l > r:
            return 0
        res = p[r]
        if l:
            res -= p[l - 1]
        return res

    keys = sorted(f.keys())
    for _ in range(q):
        u, v = getList()
        u -= 1
        ans = res
        it = bisect_left(keys, u)
        if v < a[u]:
            # Value decreased; recalculate the contribution
            it = keys[it]
            l = max(f[it], u + 1 - v)
            ans -= calc(f[it], l - 1, p) - (u - 1) * (l - f[it])
        elif v > a[u]:
            # Value increased; adjust accordingly
            if it and keys[it - 1] + 1 == u:
                l = max(f[keys[it - 1]], u + 1 - v)
                ans += calc(l, f[keys[it]] - 1, P)
        print(ans)


for _ in range(t):
    solve()


# https://github.com/VaHiX/CodeForces/