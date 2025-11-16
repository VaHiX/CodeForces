# Problem: CF 1809 F - Traveling in Berland
# https://codeforces.com/contest/1809/problem/F

"""
Code Purpose:
This solution computes the minimum cost to travel through all cities in a circular arrangement, 
where each city has a fuel station and the journey must start and end at the same city. 
The road is one-directional (clockwise), and the car's fuel tank has a fixed capacity.
The algorithm uses preprocessing to compute prefix and suffix costs, and handles special cases
involving fuel costs of 1 burle.

Algorithms/Techniques:
1. Prefix and suffix cost calculation for efficient range queries.
2. Special handling of cities with fuel cost = 1.
3. Modular arithmetic and rotation for circular permutation handling.

Time Complexity: O(n) per test case, where n is the number of cities.
Space Complexity: O(n) for storing arrays and intermediate computations.
"""

import io
import os
import sys

try:
    Z = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline
except:
    Z = lambda: sys.stdin.readline().encode()
Y = lambda: map(int, Z().split())


def f(v, k):
    # Helper function to compute effective fuel consumption with tank capacity
    return v if v <= k else v + v - k


def solve(n, k, a, b):
    # Special case handling for all cities having fuel cost 2
    if 1 not in b:
        return solve(n, k << 1, [i << 1 for i in a], [1] * n)
    # Special case: If last city does not have fuel cost 1, rotate to make it so
    if b[-1] != 1:
        i = b.index(1) + 1
        A = solve(n, k, a[i:] + a[:i], b[i:] + b[:i])
        return A[-i:] + A[:-i]
    
    # Initialize arrays
    f1 = [0]  # Prefix fuel costs from the start
    f2 = [0]  # Suffix fuel costs from the end
    s = v = 0  # s: total cost, v: current fuel required
    p = n - 1  # Point of last city with fuel cost 1
    d = [0] * n  # Distance array to track distances
    
    # Forward pass to compute f1 and d
    for i in range(n):
        if b[i] == 1:  # City has fuel cost 1
            f1.append(0)
            s += f(v + a[i - 1], k)  # Add the cost to reach this point
            v = 0
            p = i
        else:
            f1.append(f1[-1] + a[i - 1])  # Accumulate fuel cost
            v += a[i - 1]
            d[i] = p  # Track point where fuel cost 1 is last seen
    
    # Backward pass to compute f2
    v = 0
    for i in range(n - 2, -2, -1):
        if b[i] == 1:  # City has fuel cost 1
            f2.append(0)
            d[i] = f(v + a[i], k)
            v = 0
        else:
            f2.append(f2[-1] + (a[i] << 1))  # Add double of fuel needed (because of direction)
            v += a[i]
    
    # Remove initial elements
    f1 = f1[1:]
    f2 = f2[-2::-1]  # Reverse and remove last element
    
    # Final computation to get the minimum cost for each starting city
    A = []
    for i in range(n):
        if b[i] == 1:
            A.append(s)  # If city has fuel cost 1, cost is s
        else:
            A.append(s - d[d[i]] + f(f1[i], k) + f2[i])
    return A


O = []
for _ in range(*Y()):
    n, k = Y()
    a = [*Y()]
    b = [*Y()]
    O.append(" ".join(map(str, solve(n, k, a, b))))
print("\n".join(O))


# https://github.com/VaHiX/CodeForces/