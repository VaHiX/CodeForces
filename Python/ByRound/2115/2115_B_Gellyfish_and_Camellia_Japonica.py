# Problem: CF 2115 B - Gellyfish and Camellia Japonica
# https://codeforces.com/contest/2115/problem/B

"""
B. Gellyfish and Camellia Japonica

Purpose:
This code determines if there exists a valid initial array `a` such that after applying a series of 
modifications, the final array matches a given array `b`. Each modification sets `c[z] = min(c[x], c[y])`.
The problem is essentially about checking constraint consistency and reconstructing a feasible solution.

Algorithms/Techniques:
- Reverse simulation to compute candidate values for the original array.
- Forward simulation to validate if the reconstructed array leads to correct final state.

Time Complexity: O(n + q)
Space Complexity: O(n + q)

Input Format:
- Multiple test cases.
- For each test case:
  - n, q: size of array and number of operations.
  - b: target array after all operations.
  - q lines with x_i, y_i, z_i: indices for each operation.

Output Format:
- For each test case: reconstruction of `a` or "-1" if inconsistent.
"""

import sys

input = sys.stdin.readline

out = []
t = int(input())
for _ in range(t):
    n, q = map(int, input().split())
    b = list(map(int, input().split()))
    x = []
    y = []
    z = []
    for _ in range(q):
        xi, yi, zi = map(int, input().split())
        xi -= 1
        yi -= 1
        zi -= 1
        x.append(xi)
        y.append(yi)
        z.append(zi)
    a = b[:]  # Start with final array as candidate for original
    # Reverse simulation: process operations backwards to assign values
    for i in range(q)[::-1]:
        xi, yi, zi = x[i], y[i], z[i]
        old = a[zi]   # Save old value at z_i
        a[zi] = 0     # Temporarily reset z_i
        a[xi] = max(a[xi], old)  # Propagate max to x_i
        a[yi] = max(a[yi], old)  # Propagate max to y_i
    c = a[:]   # Copy the result from reverse pass
    # Forward simulation: verify consistency of assignment
    for i in range(q):
        xi, yi, zi = x[i], y[i], z[i]
        c[zi] = min(c[xi], c[yi])  # Apply operation as described
    if c == b:   # If forward simulation matches target
        out.append(" ".join(map(str, a)))
    else:
        out.append("-1")
print("\n".join(out))


# https://github.com/VaHiX/codeForces/