# Problem: CF 2021 C1 - Adjust The Presentation (Easy Version)
# https://codeforces.com/contest/2021/problem/C1

"""
Code Purpose:
This code determines whether a slideshow presentation is possible given the constraints of member movement.
The key idea is to simulate the process of presenting slides by checking if each required member is available at the front of the line or can be brought there through allowed moves.

Algorithms/Techniques:
- Greedy simulation approach
- Set-based membership checking for efficient lookup

Time Complexity: O(n + m) per test case
Space Complexity: O(n) for the set storage

The algorithm works by iterating through each slide and checking if:
1. The required member is at the front of the line (a[p])
2. Or if the required member has already been seen and is in the set
If neither condition holds, the presentation is not possible.
"""

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n, m, q = map(int, input().split())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    p = 0  # Pointer to track the current front member in the initial lineup
    s = set()  # Set to store members that have been processed (already at front or moved)
    check = 1  # Flag to indicate if slideshow is possible
    for j in range(m):
        # If the required member is at the front and we haven't exhausted the initial lineup
        if p < n and b[j] == a[p]:
            s.add(a[p])  # Add the member to the set as they are now in front
            p += 1  # Move pointer to next member
        # If the required member is already in the set (meaning it was previously moved to front)
        elif b[j] in s:
            continue  # No need to move, just continue
        else:
            # Required member is neither the front nor has been moved before => impossible
            check = 0
            break
    print("YA" if check else "TIDAK")


# https://github.com/VaHiX/CodeForces/