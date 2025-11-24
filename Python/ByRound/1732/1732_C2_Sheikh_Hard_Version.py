# Problem: CF 1732 C2 - Sheikh (Hard Version)
# https://codeforces.com/contest/1732/problem/C2

"""
Algorithm: 
- For each query [L, R], we need to find a subsegment [l, r] within [L, R] that maximizes f(l, r) = sum(l, r) - xor(l, r).
- We precompute prefix sums and prefix XORs to quickly calculate sum and xor for any interval.
- The key observation is that for maximizing f(l, r), we want sum(l, r) to be large and xor(l, r) to be small.
- A special case occurs when f(l, r) = 0, which happens when sum(l, r) = xor(l, r). 
- We preprocess an array u where u[i] is the index of the next non-zero element after i.
- For each query, we start with the full interval [L, R], find the maximum value of f(L, R) using a sliding window technique.
- Adjust the endpoints to find the minimal length interval achieving the maximum value.

Time Complexity: O(n^2) in worst case but with optimization it's much better in practice.
Space Complexity: O(n) for storing prefix sums, prefix XORs, and auxiliary arrays.
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(l, r):
    # Calculate f(l, r) = sum(l, r) - xor(l, r) using prefix arrays
    return s[r] - s[l - 1] - (x[r] ^ x[l - 1])


t = int(input())
ans = []
for _ in range(t):
    n, q = map(int, input().split())
    a = [0] + list(map(int, input().split()))  # 1-indexed array
    s, x = list(a), list(a)
    # Precompute prefix sums and prefix XORs
    for i in range(1, n + 1):
        s[i] += s[i - 1]
        x[i] ^= x[i - 1]
    
    # Create list of indices where a[i] != 0
    u = []
    for i in range(1, n + 1):
        if a[i]:
            u.append(i)
    
    # Precompute left and right boundaries for each index
    l0, r0 = [0] * (n + 1), [0] * (n + 1)
    i, j = 1, 0
    # Fill l0 array
    while j < len(u):
        l0[i] = j
        if u[j] == i:
            j += 1
        i += 1
    
    i, j = n, len(u) - 1
    # Fill r0 array
    while j >= 0:
        r0[i] = j
        if u[j] == i:
            j -= 1
        i -= 1
    
    # Process queries
    for _ in range(q):
        l, r = map(int, input().split())
        z = f(l, r)
        if not z:
            # If maximum value is 0, return any single element subsegment with non-zero value
            ans0 = [l, l]
            ans.append(" ".join(map(str, ans0)))
            continue
        i, j = l0[l], r0[r]
        # Adjust j to minimize length while maintaining maximum value
        while i < j and f(u[i], u[j - 1]) == z:
            j -= 1
        # Adjust i to minimize length while maintaining maximum value
        while i < j and f(u[i + 1], u[j]) == z:
            i += 1
        ans0 = [u[i], u[j]]
        # Extend the end of the interval to find minimal length with maximum value
        while j + 1 < len(u) and u[j + 1] <= r:
            j += 1
            while i < j and f(u[i + 1], u[j]) == z:
                i += 1
            if u[j] - u[i] < ans0[1] - ans0[0]:
                ans0 = [u[i], u[j]]
        ans.append(" ".join(map(str, ans0)))
sys.stdout.write("\n".join(ans))


# https://github.com/VaHiX/CodeForces/