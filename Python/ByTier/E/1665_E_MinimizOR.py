# Problem: CF 1665 E - MinimizOR
# https://codeforces.com/contest/1665/problem/E

"""
E. MinimizOR

Purpose:
This code solves the problem of finding the minimum bitwise OR of any pair of elements in a given subarray for multiple queries.

Algorithms/Techniques:
- Sparse Table: Used for efficient range minimum queries (RMQ) preprocessing.
- Priority Queue (Heap): Used to process intervals in order of increasing minimum value to optimize search for minimal OR.
- Bit Manipulation: Elements are encoded as (value * (n+1) + index) to store both value and position.

Time Complexity:
- Preprocessing per test case: O(n log n)
- Each query processing: O(log^2 n)
- Overall: O(t * (n log n + q * log^2 n)) 

Space Complexity:
- O(n log n) for the sparse table.
- O(q) for priority queue in worst case.

"""

import heapq
import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def sparse_table(a):
    # Build a sparse table for range minimum queries
    table = []
    s0, l = a, 1
    table.append(s0)
    while 2 * l <= len(a):
        s = [min(s0[i], s0[i + l]) for i in range(len(s0) - l)]
        table.append(list(s))
        s0 = s
        l *= 2
    return table


def get_min(l, r, table):
    # Retrieve minimum from sparse table for range [l, r]
    d = (r - l + 1).bit_length() - 1
    ans = min(table[d][l], table[d][r - pow2[d] + 1])
    return ans


t = int(input())
ans = []
pow2 = [1]
for _ in range(20):
    pow2.append(2 * pow2[-1])
inf = pow(2, 30) + 1
for _ in range(t):
    n = int(input())
    a = [0] + list(map(int, input().split()))
    # Encode values as (value * (n+1) + index) for storing both value and position
    for i in range(1, n + 1):
        a[i] *= n + 1
        a[i] += i
    table = sparse_table(a)
    q = int(input())
    for _ in range(q):
        l, r = map(int, input().split())
        ans0 = inf
        h = []
        # Push initial interval into the heap
        heapq.heappush(h, (get_min(l, r, table), l, r))
        x = []
        while len(h) and h[0][0] // (n + 1) < ans0:
            c, l, r = heapq.heappop(h)
            z = c // (n + 1)   # Extract original value from encoded format
            c %= n + 1         # Extract index from encoded format
            for i in x:
                ans0 = min(ans0, i | z)   # Update answer with OR of previous values and current
            x.append(z)
            if l ^ c:          # If left boundary is different than index
                heapq.heappush(h, (get_min(l, c - 1, table), l, c - 1))
            if c ^ r:          # If right boundary is different than index
                heapq.heappush(h, (get_min(c + 1, r, table), c + 1, r))
        ans.append(ans0)
sys.stdout.write("\n".join(map(str, ans)))


# https://github.com/VaHiX/codeForces/