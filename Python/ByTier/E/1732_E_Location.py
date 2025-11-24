# Problem: CF 1732 E - Location
# https://codeforces.com/contest/1732/problem/E

"""
Algorithm: Segment Tree with lazy propagation and precomputed values
Time Complexity: O(n * sqrt(max_value) + q * sqrt(max_value) * log(max_value))
Space Complexity: O(max_value * sqrt(max_value))

This code handles two types of queries on arrays a and b:
1. Update a range of array a with a value x
2. Find minimum value of lcm(a[i], b[i]) / gcd(a[i], b[i]) in a range

The solution uses a segmented approach with precomputation for efficiency.
"""

import io
import math
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def the_sieve_of_eratosthenes(n):
    s, x = [i & 1 for i in range(n + 1)], [2]
    s[1], s[2] = 0, 1
    for i in range(3, n + 1):
        if s[i]:
            x.append(i)
            for j in range(i * i, n + 1, 2 * i):
                s[j] = 0
    return x


def f(u, v):
    return u << 20 ^ v


def g(u, v):
    return u << 16 ^ v


def update1(l, r, u):
    lz = lazy[l >> 7]  # Get lazy value for segment
    if lz:
        # Handle partial overlap with lazy propagation
        for i in range(l & 0xFFF80, min((l & 0xFFF80) + m, n)):
            a[i] = u if l <= i < r else lz
    else:
        for i in range(l & 0xFFF80, min((l & 0xFFF80) + m, n)):
            if l <= i < r:
                a[i] = u
    lazy[l >> 7] = ok[l >> 7] = 0  # Reset lazy and ok flags
    return


def update2(j):
    # Update min value for segment j
    if ok[j]:
        return
    l, r, mi = j << 7, min((j << 7) + m, n), inf
    for i in range(l, r):
        x = a[i] * b[i] // (math.gcd(a[i], b[i]) ** 2)
        ans3[i] = x
        if mi > x:
            mi = x
    ok[j], ans2[j] = 1, mi  # Mark as updated and store minimum
    return


n, q = map(int, input().split())
a = list(map(int, input().split()))
b = list(map(int, input().split()))
l = 5 * pow(10, 4) + 5
m = 1 << 7  # Segment size (128)
m0 = (n >> 7) + 1  # Number of segments
inf = pow(10, 12) + 1
p = the_sieve_of_eratosthenes(l)  # Prime sieve
e = []
for i in range(1, l):
    for j in p:
        if i * j >= l:
            break
        e.append(f(i * j, i))  # Special encoding for factorization
le = len(e)
e.sort(reverse=True)
e1, e2 = [0] * le, [0] * le
for i in range(le):
    e1[i], e2[i] = e[i] >> 20, e[i] & 0xFFFFF  # Decode factorization
ans1 = [0] * (m0 << 16)  # Precomputed values for segments
for i in range(m0):
    dp = [inf] * l
    for j in range(i * m, min((i + 1) * m, n)):
        dp[b[j]] = b[j]
    for j, k in zip(e1, e2):
        if dp[k] > dp[j]:
            dp[k] = dp[j]
    for j in range(1, l):
        if dp[j] ^ inf:
            dp[j] //= j
    for j in range(1, l):
        dpj = dp[j]
        for k in p:
            if j * k >= l:
                break
            if dp[j * k] > k * dpj:
                dp[j * k] = k * dpj
        ans1[g(i, j)] = dpj  # Store precomputed result
ans2, ans3 = [inf] * m0, [inf] * n  # ans2 for segment min, ans3 for individual values
for i in range(n):
    x = a[i] * b[i] // (math.gcd(a[i], b[i]) ** 2)  # Compute base value
    if ans2[i >> 7] > x:
        ans2[i >> 7] = x
    ans3[i] = x
lazy, ok = [0] * m0, [1] * m0  # Lazy propagation and update flags
ans = []
for _ in range(q):
    t = list(map(int, input().split()))
    if t[0] == 1:  # Update query
        l, r, x = t[1] - 1, t[2], t[3]
        ans2[l >> 7] = ans2[(r - 1) >> 7] = inf  # Reset segment mins
        update1(l, min(r, (l | 0x7F) + 1), x)  # Handle initial partial segment
        l = min(r, (l | 0x7F) + 1)
        while l + m <= r:
            # Mark whole segments as dirty and update lazy with value x
            ans2[l >> 7], lazy[l >> 7], ok[l >> 7] = ans1[g(l >> 7, x)], x, 1
            l += m
        if l ^ r:
            update1(l, r, x)  # Handle final partial segment
    else:  # Min query
        l, r = t[1] - 1, t[2]
        ans0 = inf
        if lazy[l >> 7]:
            update1(l & 0xFFF80, min((l & 0xFFF80) + m, n), lazy[l >> 7])  # Handle lazy propagation
        update2(l >> 7)  # Update segment min if needed
        # Handle initial partial segment
        while l & 0x7F and l < r:
            if ans0 > ans3[l]:
                ans0 = ans3[l]
            l += 1
        # Handle full segments
        while l + m <= r:
            update2(l >> 7)
            if ans0 > ans2[l >> 7]:
                ans0 = ans2[l >> 7]
            l += m
        # Handle final partial segment
        if l ^ r and lazy[l >> 7]:
            update1(l & 0xFFF80, min((l & 0xFFF80) + m, n), lazy[l >> 7])
        update2(l >> 7)
        while l < r:
            if ans0 > ans3[l]:
                ans0 = ans3[l]
            l += 1
        ans.append(ans0)
sys.stdout.write("\n".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/