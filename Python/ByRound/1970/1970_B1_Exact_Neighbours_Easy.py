# Problem: CF 1970 B1 - Exact Neighbours (Easy)
# https://codeforces.com/contest/1970/problem/B1

"""
Code Purpose:
This code solves the problem of placing n wizards' houses on an n×n grid such that:
1. Each wizard's house is at a unique column (no two wizards in the same column).
2. Each wizard visits exactly one other wizard's house, which is at a distance of a[i] (from wizard i).
3. The distance is Manhattan distance.
The algorithm uses sorting and greedy placement logic, leveraging the fact that all a[i] are even to simplify placement.

Algorithms/Techniques:
- Sorting wizards by their required distance in descending order.
- Greedy placement of houses in a grid row-wise.
- Validation of final configuration against distance constraints.

Time Complexity: O(n log n) due to sorting and linear passes.
Space Complexity: O(n) for storing positions and metadata.

"""

import os.path
import sys
from random import randint

rrr = randint(8888, 88888)
if os.path.exists("input.txt"):
    sys.stdin = open("input.txt", "r")
    sys.stdout = open("output.txt", "w")
    print(rrr)


def sol():
    N = int(input())
    x = input().split()
    # Create list of (distance, original_index) pairs for sorting
    nums = [(int(x[i]), i) for i in range(N)]

    # Sort wizards by distance in descending order to process larger distances first
    nums.sort(reverse=True)
    ans = [(0, 0)] * N  # Stores (row, col) positions of each wizard's house
    met = [0] * N       # Stores the index of the wizard that wizard i should visit
    ans[nums[0][1]] = (1, 1)  # Place the wizard with the largest distance at (1,1)
    pv = 1              # Current column index for placing next wizards
    
    # Process remaining wizards greedily
    for i in range(1, N):
        re = nums[i - 1][0] - 1  # Distance difference between previous and current wizard
        if re == -1:  # Special case when distance is 0
            met[nums[i - 1][1]] = nums[i - 1][1] + 1  # Wizard visits himself
            ans[nums[i][1]] = (i + 1, pv)             # Place next wizard
            continue
        if pv - re < 1:  # Adjust column index if going out of bounds
            pv += re
        else:
            pv -= re

        # Assign position to current wizard
        ans[nums[i][1]] = (i + 1, pv)
        # Mark which wizard to visit for the previous wizard
        met[nums[i - 1][1]] = nums[i][1] + 1

    # Validate final arrangement
    mr = nums[-1][0]  # Distance of the last wizard
    mi, mj = ans[nums[-1][1]]  # Position of last wizard's house
    pis = False
    # Find a valid wizard to visit such that the distance matches
    for i in range(N):
        d = abs(ans[i][0] - mi) + abs(ans[i][1] - mj)
        if d == mr:
            pis = True
            met[nums[-1][1]] = i + 1
            break

    if pis:
        print("YES")
        for i, j in ans:
            print(i, j)
        print(*met)
    else:
        print("NO")


sol()


# https://github.com/VaHiX/CodeForces/