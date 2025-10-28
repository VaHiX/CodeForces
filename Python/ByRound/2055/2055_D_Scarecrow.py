# Problem: CF 2055 D - Scarecrow
# https://codeforces.com/contest/2055/problem/D

"""
D. Scarecrow

Algorithms/Techniques:
- Greedy approach with simulation
- Optimal movement of scarecrows to minimize crow's travel time
- Two-pointer or sequential processing of scarecrows
- Efficient handling of teleportation conditions

Time Complexity: O(n) per test case, where n is the number of scarecrows.
Space Complexity: O(1) excluding input storage.

The problem involves a crow moving along a number line and teleporting 
whenever it gets too close to a scarecrow. Scarecrows can move optimally to 
maximize the time before the crow teleports. The goal is to compute twice 
the minimum time needed for the crow to reach or exceed position ℓ.
"""

import sys

input = lambda: sys.stdin.readline().strip()
out = []
tests = int(input())
for _ in range(tests):
    n, k, l = map(int, input().split())
    k *= 2  # Double k as per problem's requirement
    l *= 2  # Double l as per problem's requirement
    v = k   # Initial teleportation boundary (based on first scarecrow)
    a = list(map(lambda x: 2 * int(x), input().split()))  # Double the positions for easier calculation later
    ans = a[0]  # Start at first scarecrow's position
    
    for i in range(1, n):
        if a[i] > v:
            # If current scarecrow is ahead of the boundary, adjust it
            # and update teleportation condition
            a[i] = max(v, a[i] - ans)
            ans += (a[i] - v) // 2  # Increment time by half difference
            v = (v + a[i]) // 2 + k  # New teleportation boundary based on adjusted position
        else:
            # If current scarecrow is behind or at the boundary, move it
            a[i] = min(v, a[i] + ans)
            v = a[i] + k  # Update teleportation boundary
    
    if v < l:
        # If final boundary is less than target position,
        # adjust time to reach the required limit
        ans += l - v
    
    out.append(ans)

print(*out, sep="\n")


# https://github.com/VaHiX/codeForces/