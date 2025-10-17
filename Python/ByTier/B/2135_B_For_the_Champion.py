# Problem: CF 2135 B - For the Champion
# https://codeforces.com/contest/2135/problem/B

"""
B. For the Champion

Purpose:
This code solves an interactive problem where a robot must determine its initial coordinates (X,Y) on an infinite 2D grid using queries to move in four directions (up, down, left, right) and receive Manhattan distances to anchor points.

Algorithm:
The approach uses geometric properties of Manhattan distance and binary search principles. By moving the robot far away from all anchor points in specific directions (U, L, D), we can determine bounds or key values. These are then used to compute the final position through algebraic manipulation.

Time Complexity: O(n) per test case, where n is the number of anchor points.
Space Complexity: O(1), as we only store necessary variables for computation.

Techniques:
- Interactive problem handling with queries
- Geometric analysis using Manhattan distance
- Linear system solving (algebraic derivation)
"""

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n, k = int(input()), 10**9
    u = v = -float("inf")
    for i in range(n):
        i, j = map(int, input().split())
        u = max(u, i + j)      # Maximum of (x + y) among all anchor points
        v = max(v, i - j)      # Maximum of (x - y) among all anchor points
    
    # Querying four directions to compute key values
    print(f"? U {k}", flush=True)
    input()
    print(f"? U {k}", flush=True)
    input()
    print(f"? R {k}", flush=True)
    input()
    print(f"? R {k}", flush=True)
    b = int(input())           # Distance after moving up then right
    
    print(f"? D {k}", flush=True)
    input()
    print(f"? D {k}", flush=True)
    input()
    print(f"? D {k}", flush=True)
    input()
    print(f"? D {k}", flush=True)
    c = int(input())           # Distance after moving down then right
    
    # Calculate p and q from the equations derived using geometry
    # Based on Manhattan distance properties:
    # p = (distance_up_right - 4*k + max(x+y)) 
    # q = (distance_down_right - 4*k + max(x-y))
    p = b - 4 * k + u
    q = c - 4 * k + v
    
    # Solve for x and y:
    # x = (p+q)/2, y = (p-q)/2
    x = (p + q) // 2
    y = (p - q) // 2
    
    print(f"! {x} {y}", flush=True)


# https://github.com/VaHiX/codeForces/