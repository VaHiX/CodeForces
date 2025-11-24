# Problem: CF 1835 C - Twin Clusters
# https://codeforces.com/contest/1835/problem/C

"""
Algorithm: Twin Clusters
Purpose: Find two disjoint galaxy clusters with equal traits (bitwise XOR of galaxy values).
Techniques: 
  - Prefix XOR for efficient range XOR computation
  - Brute-force for small k (k <= 4)
  - Randomized approach for larger k (k > 4)
  - Hash map for collision detection in randomized approach

Time Complexity:
  - For k <= 4: O(n^4) where n = 2^(k+1) 
  - For k > 4: O(100 * n) average case due to random sampling
Space Complexity:
  - O(n) for prefix XOR array and hash maps
"""

import io
import os
import random
import sys
from collections import defaultdict

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v):
    return u * (n + 1) + v


t = int(input())
ans = []
pow2 = [1]
for _ in range(40):
    pow2.append(2 * pow2[-1])
r0 = random.randint(1, pow2[40] - 1)
for _ in range(t):
    k = int(input())
    n = pow2[k + 1]
    g = list(map(int, input().split()))
    x = -1
    g0 = list(g)
    g0.sort()
    for i in range(n - 1):
        if g0[i] == g0[i + 1]:
            x = g0[i]
            break
    if x ^ -1:  # If x is not -1, meaning we found a duplicate
        ans0 = []
        for i in range(n):
            if g[i] == x:
                ans0.append(i + 1)
                ans0.append(i + 1)
            if len(ans0) == 4:
                break
    elif k <= 4:
        # Use brute force for small inputs
        u = [0]
        for i in g:
            u.append(u[-1] ^ i)
        ans0 = []
        for i in range(n + 1):
            for j in range(i + 1, n + 1):
                for k in range(j, n + 1):
                    for l in range(k + 1, n + 1):
                        if u[i] ^ u[j] == u[k] ^ u[l]:  # Check if traits are equal
                            ans0 = [i + 1, j, k + 1, l]  # Return 1-indexed ranges
                            break
                    if ans0:
                        break
                if ans0:
                    break
            if ans0:
                break
    else:
        # Use randomized approach for large inputs
        u = [0]
        for i in g:
            u.append(u[-1] ^ i)
        x = []
        for _ in range(100):
            l, r = random.randint(0, n - 1), random.randint(0, n - 1)
            if l > r:
                l, r = r, l
            x.append(u[l] ^ u[r + 1])  # Compute random range XORs
        y = [[] for _ in range(100)]
        d = defaultdict(lambda: [])
        ok = 0
        for i in range(n + 1):
            for j in range(100):
                if u[i] ^ x[j] ^ r0 in d:  # Check for a match in hash map
                    for k in d[u[i] ^ x[j] ^ r0]:
                        y[j].append(f(k, i))  # Store indices as encoded pair
                if len(y[j]) >= 3:
                    ok = 1
                    break
            if ok:
                break
            d[u[i] ^ r0].append(i)  # Hash current prefix XOR
        ans0 = []
        for z in y:
            if len(z) == 2:
                l1, r1 = divmod(z[0], n + 1)  # Decode first pair
                l2, r2 = divmod(z[1], n + 1)  # Decode second pair
                if l1 ^ l2 and r1 ^ r2:  # Ensure disjointness
                    ans0 = [l1, l2, r1, r2]
                    ans0.sort()
                    ans0[0] += 1
                    ans0[2] += 1
            elif len(z) == 3:
                # Handle three matches - use brute force to validate disjoint intervals
                l1, r1 = divmod(z[0], n + 1)
                l2, r2 = divmod(z[1], n + 1)
                l3, r3 = divmod(z[2], n + 1)
                x = [l1, l2, l3, r1, r2, r3]
                x.sort()
                for i in range(6):
                    for j in range(i + 1, 6):
                        for k in range(j, 6):
                            for l in range(k + 1, 6):
                                if (
                                    u[x[i]] ^ u[x[j]] == u[x[k]] ^ u[x[l]]
                                    and x[i] < x[j]
                                    and x[k] < x[l]
                                ):
                                    ans0 = [x[i] + 1, x[j], x[k] + 1, x[l]]
                                    break
                            if ans0:
                                break
                        if ans0:
                            break
                    if ans0:
                        break
            if ans0:
                break
    if not ans0:  # If no twin clusters found
        ans0 = [-1]
    ans.append(" ".join(map(str, ans0)))
sys.stdout.write("\n".join(ans))


# https://github.com/VaHiX/CodeForces/