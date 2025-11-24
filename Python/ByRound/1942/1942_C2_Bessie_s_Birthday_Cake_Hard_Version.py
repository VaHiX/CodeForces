# Problem: CF 1942 C2 - Bessie's Birthday Cake (Hard Version)
# https://codeforces.com/contest/1942/problem/C2

"""
Algorithm: Dynamic Programming + Greedy Construction
Purpose: To maximize the number of triangular pieces from a polygon after choosing additional vertices.
Time Complexity: O(x log x) per test case due to sorting and linear iteration.
Space Complexity: O(x) for storing the list of differences between chosen vertices.

Approach:
1. The idea is to compute the gaps between consecutive chosen vertices.
2. Sort these gaps.
3. Greedily try to reduce large gaps by placing new vertices to break them into smaller parts.
4. Each gap of size greater than 2 contributes (gap_size - 1) to the total count of triangles.
5. Use the available y vertices optimally to minimize the number of large gaps.
"""

import sys


def input():
    return sys.stdin.readline().rstrip()


for i in range(int(input())):
    n, x, y = map(int, input().split())
    lst = sorted(map(int, input().split()))
    lstx = []
    # Compute gaps between consecutive chosen vertices (modular arithmetic)
    for i in range(x):
        lstx.append((lst[i] - lst[i - 1]) % n)
    lstx.sort()
    
    # First greedy pass: try to reduce even gaps by placing vertices optimally
    for i in range(x):
        if lstx[i] > 2 and lstx[i] % 2 == 0:
            if y:
                t = min(2 * y, (lstx[i] - 2))  # How many vertices to place
                lstx[i] -= t  # Reduce the gap
                y -= t // 2   # Decrease available y accordingly
            else:
                break
    
    # Second greedy pass: reduce remaining large gaps
    if y:
        for i in range(x):
            if lstx[i] > 2:
                if y:
                    t = min(2 * y, (lstx[i] // 2 * 2))  # Reduce the gap as much as possible
                    lstx[i] -= t
                    y -= t // 2
                else:
                    break
    
    # Count total triangles: base = n - 2, then subtract contributions from large gaps
    ans = n - 2
    for i in range(x):
        if lstx[i] > 2:
            ans -= lstx[i] - 1  # Contribution adjustment
    
    print(ans)


# https://github.com/VaHiX/CodeForces/