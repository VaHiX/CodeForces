# Problem: CF 1993 F1 - Dyn-scripted Robot (Easy Version)
# https://codeforces.com/contest/1993/problem/F1

"""
Algorithm: Simulation with Hashing and Binary Search
Time Complexity: O(n log n + k * n)
Space Complexity: O(n)

This solution simulates the robot moving according to a script, handling boundary
conditions by flipping characters in the script when crossing borders. It uses
hashing and binary search to efficiently determine how many times (0,0) is visited
over k iterations of the script. The key insight is that the robot moves in a
periodic pattern modulo 2*w and 2*h due to reflections at boundaries.
"""

import bisect
import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v):
    # Simple hash function to map (x,y) to an integer for comparison
    return u << 30 ^ v


t = int(input())
ans = []
d = {"L": (-1, 0), "R": (1, 0), "U": (0, 1), "D": (0, -1)}
for _ in range(t):
    n, k, w, h = map(int, input().split())
    s = list(input().decode().rstrip())
    u = [0] * n
    x, y = 0, 0
    # Simulate movement and record hashed positions
    for i in range(n):
        dx, dy = d[s[i]]
        x, y = (x + dx) % (2 * w), (y + dy) % (2 * h)
        u[i] = f(x, y)
    u.sort()
    # Precompute count of consecutive same hash values
    c = [1] * (n + 1)
    for i in range(n - 2, -1, -1):
        if u[i] == u[i + 1]:
            c[i] = c[i + 1] + 1
    ans0 = 0
    dx, dy, x, y = x, y, 0, 0
    # Run simulation k times
    for _ in range(k):
        i = f(x, y)
        j = bisect.bisect_left(u, i)
        if j != n and u[j] == i:
            ans0 += c[j]
        x, y = (x - dx) % (2 * w), (y - dy) % (2 * h)
    ans.append(ans0)
sys.stdout.write("\n".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/