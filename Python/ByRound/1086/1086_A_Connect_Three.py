# Problem: CF 1086 A - Connect Three
# https://codeforces.com/contest/1086/problem/A

"""
Code Purpose:
This program determines the minimum number of 1x1 plots to clear in a grid such that 
three given plots (A, B, C) become mutually reachable via adjacent cleared plots. 
It uses geometric reasoning to find the optimal path between the three points by 
considering different "L-shaped" paths and counting the unique cleared plots required.

Algorithms/Techniques:
- Brute-force enumeration over 6 possible orderings of the points (A, B, C).
- For each ordering, generate L-shaped paths connecting pairs of points.
- For each L-shape, compute a set of plots that must be cleared to make the connection.
- Union all required plots across all connections, and keep track of the minimum.

Time Complexity: O(1) - Since the grid is bounded (up to 1000x1000), and we only check a 
fixed number of combinations (6 orderings x 2 configurations per pair = 12), the algorithm 
runs in constant time.

Space Complexity: O(1) - The maximum size of the set storing cleared plots is bounded by 
a constant due to the constraints on input coordinates.
"""

import sys

input = sys.stdin.buffer.readline

# Predefined orderings for processing three points in different orders
orders = [(0, 1, 2), (0, 2, 1), (1, 0, 2), (1, 2, 0), (2, 0, 1), (2, 1, 0)]


def process(A, B, C):
    # Store the three points in a list for easier handling
    L = [A, B, C]
    # Initialize answer with a large value and None
    answer = [float("inf"), None]
    
    # Try all permutations of A, B, C as (first, second, third) in the chain
    for i, j, k in orders:
        x1, y1 = L[i]
        x2, y2 = L[j]
        x3, y3 = L[k]
        
        # Two possible L-shaped paths between first two points (x1,y1) and (x2,y2)
        for l1 in range(2):
            S = set([])
            if l1 == 0:
                # Horizontal then vertical path
                for x0 in range(min(x1, x2), max(x1, x2) + 1):
                    S.add((x0, y1))
                for y0 in range(min(y1, y2), max(y1, y2) + 1):
                    S.add((x2, y0))
            else:
                # Vertical then horizontal path
                for y0 in range(min(y1, y2), max(y1, y2) + 1):
                    S.add((x1, y0))
                for x0 in range(min(x1, x2), max(x1, x2) + 1):
                    S.add((x0, y2))
                
            # Two possible L-shaped paths between second and third points (x2,y2) and (x3,y3)
            for l2 in range(2):
                S_copy = S.copy()
                if l2 == 0:
                    # Horizontal then vertical path
                    for x0 in range(min(x2, x3), max(x2, x3) + 1):
                        S_copy.add((x0, y2))
                    for y0 in range(min(y2, y3), max(y2, y3) + 1):
                        S_copy.add((x3, y0))
                else:
                    # Vertical then horizontal path
                    for y0 in range(min(y2, y3), max(y2, y3) + 1):
                        S_copy.add((x2, y0))
                    for x0 in range(min(x2, x3), max(x2, x3) + 1):
                        S_copy.add((x0, y3))
                        
                # Update the minimum number of plots to be cleared
                entry = [len(S_copy), S_copy]
                answer = min(answer, entry)
    return answer


# Read input coordinates for the three points A, B, C
A = [int(x) for x in input().split()]
B = [int(x) for x in input().split()]
C = [int(x) for x in input().split()]

# Process and get minimum required cleared plots
a1, a2 = process(A, B, C)

# Output result
print(a1)
for x, y in a2:
    sys.stdout.write(f"{x } {y }\n")


# https://github.com/VaHiX/CodeForces/