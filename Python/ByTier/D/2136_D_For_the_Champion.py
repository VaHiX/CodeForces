# Problem: CF 2136 D - For the Champion
# https://codeforces.com/contest/2136/problem/D

# Flowerbox describing code purpose, algorithms, time and space complexity
"""
Problem: Find initial coordinates (X, Y) of a robot on an infinite 2D plane using Manhattan distance queries to anchor points.

Algorithms/Techniques:
- Coordinate transformation using sum and difference of x and y coordinates (x+y and x-y)
- Binary search-like approach to determine the range of possible coordinates
- Interactive problem solving with at most 10 queries

Time Complexity: O(n log(max_coordinate)) where n is number of anchor points
Space Complexity: O(n) for storing anchor point coordinates
"""

import sys

input = sys.stdin.readline

D = ["L", "R", "U", "D"]


def go(dir, k):
    print(f"? {D[dir]} {k}")
    sys.stdout.flush()


T = int(input())
for _ in range(T):
    n = int(input())
    a = []
    b = []
    c = []
    for _ in range(n):
        x, y = map(int, input().split())
        a.append((x, y))
        b.append(x + y)
        c.append(x - y)
    c.sort()
    b.sort()
    mxb = b[-1]
    mxc = c[-1]
    con = 4 * 10**9
    # Move down by 10^9 units to get distance d1
    go(2, 10**9)
    input()
    # Move down again by 10^9 units to confirm distance d1  
    go(2, 10**9)
    input()
    # Move right by 10^9 units to get distance d2
    go(1, 10**9)
    input()
    # Move right again by 10^9 units to confirm distance d2
    go(1, 10**9)
    d1 = int(input())
    # Move down by 10^9 units to get another distance
    go(3, 10**9)
    input()
    # Move down again by 10^9 units to confirm distance
    go(3, 10**9)
    input()
    # Move down again by 10^9 units to confirm distance  
    go(3, 10**9)
    input()
    # Move down again by 10^9 units to get final distance
    go(3, 10**9)
    d2 = int(input())
    # Use the equations to reconstruct original coordinates
    x = (mxb + mxc + d1 + d2 - 2 * con) // 2
    y = x - mxc - d2 + con
    print(f"! {x} {y}")
    sys.stdout.flush()


# https://github.com/VaHiX/codeForces/