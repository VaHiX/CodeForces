# Problem: CF 1979 E - Manhattan Triangle
# https://codeforces.com/contest/1979/problem/E

"""
Manhattan Triangle Problem

Algorithm:
This solution uses a coordinate transformation and hash map lookup to find a Manhattan triangle.
The approach transforms the coordinate system to work with the properties of Manhattan distance.

Time Complexity: O(n log n) per test case
Space Complexity: O(n) for storing points and hash maps

The key idea is to use a hash function to map coordinates to indices, and then search for valid triangles
by iterating through sorted points and checking if three points form a valid Manhattan triangle with
distance d.

The Manhattan triangle is characterized by having all pairwise Manhattan distances equal to d.
We use a transformation where each point is mapped to a unique key using a hash function,
then we look for combinations that satisfy the triangle condition.
"""

import bisect
import io
import os
import random
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v):
    # Hash function to combine coordinates and index
    return u << 20 ^ v


t = int(input())
ans = []
rr = random.randint(1, 1 << 40)
for t0 in range(t):
    n, d = map(int, input().split())
    x0, y0 = [0] * n, [0] * n
    for i in range(n):
        x, y = map(int, input().split())
        x0[i], y0[i] = x, y
    # Normalize coordinates to avoid negative values
    mx, my = min(x0), min(y0)
    for i in range(n):
        x0[i] -= mx
        y0[i] -= my
    ans0 = [0] * 3
    u = [0] * n
    d1 = d >> 1 # Half the distance for triangle calculations
    for _ in range(2): # Try both orientations of Y-axis
        d0 = dict()
        for i in range(n):
            u[i] = f(x0[i] + y0[i], i) # Store sum of coordinates and index
            d0[f(x0[i], y0[i]) ^ rr] = i # Map coordinates to index with hash
        u.sort() # Sort by sum of coordinates
        p, a, l, r = u[0] >> 20, [], 0, 0 # p = current sum, a = list of x-coordinates, l/r = pointers
        for v in u:
            p0 = v >> 20 # Extract sum value
            if p ^ p0: # If sum changed
                a.sort() # Sort x-coordinates
                while l < n and p - (u[l] >> 20) >= d and not ans0[0]: # Check for valid triangle
                    if a and p - (u[l] >> 20) == d:
                        i = u[l] & 0xFFFFF # Extract index
                        xi, yi = x0[i], y0[i]
                        w = min(bisect.bisect_left(a, f(xi, 0)), len(a) - 1) # Binary search
                        j = a[w] & 0xFFFFF
                        xj, yj = x0[j], y0[j]
                        xk, yk = xj + d1, yj - d1 # Compute k point (triangle vertex)
                        # Validate triangle properties
                        if (
                            abs(xi - xj) + abs(yi - yj)
                            == abs(xi - xk) + abs(yi - yk)
                            == d
                        ):
                            k = d0[f(xk, yk) ^ rr] # Get index of k point
                            ans0 = [i + 1, j + 1, k + 1] # Convert to 1-based indexing
                    l += 1
                while r < n and p - (u[r] >> 20) >= -d and not ans0[0]: 
                    if a and p - (u[r] >> 20) == -d:
                        i = u[r] & 0xFFFFF
                        xi, yi = x0[i], y0[i]
                        w = min(bisect.bisect_left(a, f(xi - d, 0)), len(a) - 1)
                        j = a[w] & 0xFFFFF
                        xj, yj = x0[j], y0[j]
                        xk, yk = xj + d1, yj - d1
                        if (
                            abs(xi - xj) + abs(yi - yj)
                            == abs(xi - xk) + abs(yi - yk)
                            == d
                        ):
                            k = d0[f(xk, yk) ^ rr]
                            ans0 = [i + 1, j + 1, k + 1]
                    r += 1
                p, a = p0, [] # Reset current sum and point list
            if ans0[0]:
                break
            i = v & 0xFFFFF
            x, y = x0[i], y0[i]
            if d1 <= y and f(x + d1, y - d1) ^ rr in d0: # Check if potential triangle exists
                a.append(f(x, i)) # Add x coordinate to list
        a.sort() # Sort x-coordinates
        while l < n and p - (u[l] >> 20) >= d and not ans0[0]:
            if a and p - (u[l] >> 20) == d:
                i = u[l] & 0xFFFFF
                xi, yi = x0[i], y0[i]
                w = min(bisect.bisect_left(a, f(xi, 0)), len(a) - 1)
                j = a[w] & 0xFFFFF
                xj, yj = x0[j], y0[j]
                xk, yk = xj + d1, yj - d1
                if abs(xi - xj) + abs(yi - yj) == abs(xi - xk) + abs(yi - yk) == d:
                    k = d0[f(xk, yk) ^ rr]
                    ans0 = [i + 1, j + 1, k + 1]
            l += 1
        while r < n and p - (u[r] >> 20) >= -d and not ans0[0]:
            if a and p - (u[r] >> 20) == -d:
                i = u[l] & 0xFFFFF
                xi, yi = x0[i], y0[i]
                w = min(bisect.bisect_left(a, f(xi - d, 0)), len(a) - 1)
                j = a[w] & 0xFFFFF
                xj, yj = x0[j], y0[j]
                xk, yk = xj + d1, yj - d1
                if abs(xi - xj) + abs(yi - yj) == abs(xi - xk) + abs(yi - yk) == d:
                    k = d0[f(xk, yk) ^ rr]
                    ans0 = [i + 1, j + 1, k + 1]
            r += 1
        if ans0[0]:
            break
        m = max(y0)
        for i in range(n):
            y0[i] = m - y0[i] # Flip y-axis for second orientation
    ans.append(" ".join(map(str, ans0)))
sys.stdout.write("\n".join(ans))


# https://github.com/VaHiX/CodeForces/