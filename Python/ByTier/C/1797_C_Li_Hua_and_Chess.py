# Problem: CF 1797 C - Li Hua and Chess
# https://codeforces.com/contest/1797/problem/C

"""
Algorithm: Interactive Chess King Positioning
Techniques: Binary Search, Geometric Analysis

Time Complexity: O(1) per test case (constant number of queries)
Space Complexity: O(1) (only using a few variables)

The solution uses three queries to determine the king's position:
1. Query (1,1) to get the distance d1 from the king to (1,1)
2. Query (u,v) where u=min(d1+1,n), v=min(d1+1,m) to get distance d2
3. Based on d1 and d2, compute possible positions of the king and query one of them
   to confirm the correct position.

This approach works because:
- The king can move in 8 directions (up, down, left, right, and diagonals)
- Given two distances from two query points, we can deduce the king's location
- After computing possible candidates, a third query confirms the exact position
"""

import os
import sys

input = sys.stdin.buffer.readline


def f(r, c):
    # Send query for cell (r,c) and read response
    os.write(1, b"%s %d %d\n" % (a, r, c))
    return int(input())


t = int(input())
a, b = "?".encode(), "!".encode()
for _ in range(t):
    n, m = map(int, input().split())
    d1 = f(1, 1)  # Distance from king to (1,1)
    u, v = min(d1 + 1, n), min(d1 + 1, m)  # Choose a point based on d1
    d2 = f(u, v)  # Distance from king to (u,v)
    x = []  # Store possible positions
    
    # Check if (u - d2, v) could be king's position
    if u - d2 >= 1 and max(abs(u - d2 - 1), abs(v - 1)) == d1:
        x.append((u - d2, v))
    
    # Check if (u, v - d2) could be king's position
    if v - d2 >= 1 and max(abs(u - 1), abs(v - d2 - 1)) == d1:
        x.append((u, v - d2))
    
    # Query one of the possible positions to confirm
    r, c = x[0] if not f(x[0][0], x[0][1]) else x[1]
    
    # Output the final answer
    os.write(1, b"%s %d %d\n" % (b, r, c))

exit()


# https://github.com/VaHiX/CodeForces/