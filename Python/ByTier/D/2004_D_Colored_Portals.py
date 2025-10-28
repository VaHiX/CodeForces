# Problem: CF 2004 D - Colored Portals
# https://codeforces.com/contest/2004/problem/D

"""
D. Colored Portals

Purpose:
This code solves a problem where we have n cities on a straight line, each with two colored portals (from set {B, G, R, Y}).
We must answer q queries asking for the minimum cost to travel between two cities using portal connections.
Each move from city i to city j costs |i - j| coins if they share a portal color.
The code uses pre-processing and efficient lookups with left/right boundary tracking.

Algorithms/Techniques:
- Preprocessing with left and right pass to track nearest nodes of different colors
- Color mapping using index-based representation for constant time access
- Efficient range queries with conditional logic to calculate minimum travel cost

Time Complexity: O(n + q) per test case, where n is number of cities, q is number of queries.
Space Complexity: O(n) for storing arrays and mappings.
"""

import io
import os
import sys

try:
    Z = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline  # Fast input reading
except:
    Z = lambda: sys.stdin.readline().encode()  # Fallback for stdin

Y = lambda: map(int, Z().split())  # Parse integers from input line
O = []  # Output list

# Color mapping: BG=0, BR=1, BY=2, GR=3, GY=4, RY=5
arr = [b"BG", b"BR", b"BY", b"GR", b"GY", b"RY"]
d = dict((arr[i], i) for i in range(6))

for _ in range(*Y()):  # Process each test case
    n, q = Y()
    a = [d[s] for s in Z().split()]  # Convert city portals to indices
    
    # L[i] = furthest index where a different color portal exists (excluding current and opposite)
    # R[i] = nearest index with a different color portal (excluding current and opposite)
    L = [-1] * n
    R = [-1] * n
    B = [-1] * 6  # Track last occurrence of each color
    
    # Left pass: calculate L values (leftmost valid portals for each node)
    for i in range(n):
        # Find maximum index among all other colors
        L[i] = max(B[j] for j in range(6) if j != a[i] and j != 5 - a[i])
        B[a[i]] = i  # Update latest index of current color
    
    # Reset B to mark end of array (n)
    B = [n] * 6
    # Right pass: calculate R values (rightmost valid portals for each node)
    for i in range(n - 1, -1, -1):
        R[i] = min(B[j] for j in range(6) if j != a[i] and j != 5 - a[i])
        B[a[i]] = i  # Update earliest index of current color
    
    # Process queries
    for i in range(q):
        x, y = sorted(Y())  # Ensure x <= y
        x -= 1; y -= 1  # Convert to zero-based indexing
        
        # If no way to reach (opposite colors), return direct distance
        if a[x] != 5 - a[y] or R[x] < y:
            O.append(y - x)
            continue
            
        # Initialize values for cost calculation
        v1 = v2 = 3 * n
        
        # If there's a valid right boundary, compute path via right node
        if R[y] < n:
            v1 = 2 * R[y] - y - x
            
        # If there's a valid left boundary, compute path via left node
        if L[x] >= 0:
            v2 = y + x - 2 * L[x]
            
        # Select the minimum cost
        if v2 < v1:
            v1 = v2
            
        # If minimal cost still too large (impossible), return -1
        if v1 < 3 * n:
            O.append(v1)
            continue
        O.append(-1)

print("\n".join(map(str, O)))


# https://github.com/VaHiX/codeForces/