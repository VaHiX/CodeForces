# Problem: CF 2089 B2 - Canteen (Hard Version)
# https://codeforces.com/contest/2089/problem/B2

"""
B2. Canteen (Hard Version)

Algorithm: Binary search + Sliding window approach
Time Complexity: O(n * log(sum_a)) where n is the length of arrays and sum_a is the sum of array a
Space Complexity: O(n) for storing prefix sums and temporary arrays

This solution uses binary search on the number of rounds to find minimum rounds needed.
It simulates the process of distributing elements in a circular manner over rounds,
with optimization using prefix sums and sliding window techniques to efficiently check
if a certain number of rounds is sufficient given exactly k changes to array a.
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def solve646():
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    
    # If sum of a equals k, no rounds are needed
    if sum(a) == k:
        return 0
    
    # Reduce initial excess in a over b by assigning min(a[i], b[i]) to both
    for i in range(n):
        d = min(a[i], b[i])
        a[i] -= d
        b[i] -= d
    
    # Compute prefix sums of (a[i] - b[i]) differences
    ps = [0] * (n + 1)
    j = 0
    for i in range(n):
        ps[i] = ps[i - 1] + a[i] - b[i]
        if ps[i] < ps[j]:
            j = i
    # Rotate arrays to optimize prefix sum computation
    j += 1
    a = a[j:] + a[:j]
    b = b[j:] + b[:j]
    
    # Binary search on answer rounds
    l, r = 0, n
    while l + 1 < r:
        m = (l + r) // 2
        aa = a[:]
        s = []
        for i in range(n):
            s.append(i)
            x = b[i]
            # Simulate distribution of x from b[i] backwards through sliding window
            while x and s and i - s[-1] < m:
                d = min(x, aa[s[-1]])
                x -= d
                aa[s[-1]] -= d
                if aa[s[-1]] == 0:
                    s.pop()
        # If remaining a elements <= k changes allowed, this m is valid
        if sum(aa) <= k:
            r = m
        else:
            l = m
    return r


res_test = []
for _ in range(int(input())):
    res_test.append(solve646())
sys.stdout.write("\n".join(map(str, res_test)))


# https://github.com/VaHiX/codeForces/