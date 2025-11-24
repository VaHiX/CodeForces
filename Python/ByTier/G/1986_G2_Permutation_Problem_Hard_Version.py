# Problem: CF 1986 G2 - Permutation Problem (Hard Version)
# https://codeforces.com/contest/1986/problem/G2

"""
Algorithm: 
- This code solves a problem involving counting pairs (i, j) such that p[i] * p[j] is divisible by i * j.
- It uses number-theoretic techniques including:
    - Preprocessing divisors using sieve-like methods
    - GCD-based grouping of indices
    - Efficient lookup using prefix sums and segmented arrays
- Time Complexity: O(n log n) per test case
- Space Complexity: O(n)
"""

import math

t = int(input())
ans = []
for _ in range(t):
    n = int(input())
    p = [0] + list(map(int, input().split()))  # 1-indexed permutation
    s0 = [0] * (n + 3)
    
    # Precompute number of multiples for each index
    for i in range(1, n + 1):
        for j in range(i, n + 1, i):
            s0[j + 2] += 1
    # Convert to prefix sum
    for i in range(1, n + 3):
        s0[i] += s0[i - 1]
    m = s0[-1]
    d = [0] * m
    
    # Assign values to sorted arrays based on multiples
    for i in range(1, n + 1):
        for j in range(i, n + 1, i):
            d[s0[j + 1]] = i
            s0[j + 1] += 1
    
    # Prepare for grouping by GCD
    s1, s2 = [0] * (n + 3), [0] * (n + 3)
    u0, v0 = [0] * (n + 1), [0] * (n + 1)
    
    # Compute simplified fractions u/v = i/p[i] (divide by GCD)
    for i in range(1, n + 1):
        g = math.gcd(i, p[i])
        u, v = i // g, p[i] // g
        u0[i], v0[i] = u, v
        s1[u + 2] += 1
        s2[v + 2] += 1
    
    # Convert counts to prefix sums
    for i in range(1, n + 3):
        s1[i] += s1[i - 1]
        s2[i] += s2[i - 1]
    
    # Sort indices by reduced fractions
    uu, vv = [0] * n, [0] * n
    for i in range(1, n + 1):
        u, v = u0[i], v0[i]
        uu[s1[u + 1]], vv[s2[v + 1]] = i, i
        s1[u + 1] += 1
        s2[v + 1] += 1
    
    # Main counting logic
    cnt = [0] * (n + 1)
    ans0 = 0
    for i in range(1, n + 1):
        if s1[i] == s1[i + 1]:
            continue
        # Count all valid v such that v | u
        for j in range(i, n + 1, i):
            for k in range(s2[j], s2[j + 1]):
                u = u0[vv[k]]
                cnt[u] += 1
        # For each u such that u | v, add to answer
        for j in range(s1[i], s1[i + 1]):
            v = v0[uu[j]]
            for k in range(s0[v], s0[v + 1]):
                ans0 += cnt[d[k]]
        # Reset count
        for j in range(i, n + 1, i):
            for k in range(s2[j], s2[j + 1]):
                u = u0[vv[k]]
                cnt[u] -= 1
    
    # Adjust overcounting (pairs where i = j)
    for u, v in zip(u0[1:], v0[1:]):
        if not v % u:
            ans0 -= 1
    ans0 >>= 1
    ans.append(ans0)
print("\n".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/