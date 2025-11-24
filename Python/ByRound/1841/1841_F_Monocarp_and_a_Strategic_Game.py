# Problem: CF 1841 F - Monocarp and a Strategic Game
# https://codeforces.com/contest/1841/problem/F

"""
Code Purpose:
This code solves the Monocarp and a Strategic Game problem by determining the optimal 
set of groups to accept to maximize the score, which is computed as m + k where m is 
the number of inhabitants and k is the sum of happiness values. 

The solution uses a geometric approach: each group is represented as a vector in 2D 
space (u, v) where u = a - b and v = c - d (based on race interactions). It then finds 
the maximum sum of squares of prefix sums of these vectors, which corresponds to the 
maximum possible score.

Algorithms/Techniques:
- Vector representation of groups
- Geometric interpretation using 2D vectors
- Sliding window with convex hull optimization
- Prefix sum and dynamic programming concepts
- Angular sorting to simplify geometric reasoning

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing vectors and auxiliary arrays
"""

import cmath
import io
import os

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

n = int(input())
u0, v0, s = [0] * n, [0] * n, []
inf = pow(10, 13)
for i in range(n):
    a, b, c, d = map(int, input().split())
    u, v = a - b, c - d
    u0[i], v0[i] = u, v
    x = int(cmath.phase(complex(u, v)) * inf)  # Compute angular component
    s.append(x * n + i)  # Encode angle+index for sorting

u, v = [], []
for i in sorted(s):
    j = i % n
    u.append(u0[j])
    v.append(v0[j])

u, v = u + u, v + v  # Duplicate arrays to simulate circular structure
l = 0
ans = 0
x, y = 0.0, 0.0  # Prefix sum of u,v components
for r in range(2 * n):
    x += u[r % n]
    y += v[r % n]
    if l + n == r:
        x -= u[l]
        y -= v[l]
        l += 1
    z = x * x + y * y  # Square of norm (sum of squares of prefix)
    while l < r:
        ul, vl = u[l % n], v[l % n]
        z0 = (x - ul) * (x - ul) + (y - vl) * (y - vl)
        if z0 < z:
            break
        x, y, z = x - ul, y - vl, z0
        l += 1
    ans = max(ans, z)
ans = int(ans)
print(ans)


# https://github.com/VaHiX/CodeForces/