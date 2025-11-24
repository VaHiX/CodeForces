# Problem: CF 1611 G - Robot and Candies
# https://codeforces.com/contest/1611/problem/G

"""
Code Purpose:
This code solves the problem of finding the minimum number of times a robot needs to be placed 
on the topmost row of a grid to collect all candies. The robot moves in a specific pattern: 
from (x, y) it can go to (x+1, y+1) or (x+1, y-1). The key insight is to group cells by their 
diagonal (i + j) and process them in pairs to determine how many passes are needed.

Algorithms/Techniques:
- Diagonal grouping: Group cells based on the sum of their coordinates (i + j)
- Greedy approach with interval merging: For each group, simulate how the robot can traverse
  through the grid and merge overlapping intervals.

Time Complexity: O(n * m * log(n * m))
Space Complexity: O(n * m)

The algorithm essentially builds an interval representation of reachable positions for each 
diagonal group and then merges overlapping intervals to count the minimum number of paths.
"""

import sys
from bisect import bisect_left

input = sys.stdin.readline


def solve():
    # Read blank line
    input()
    n, m = map(int, input().split())
    # Preallocate list of lists for each diagonal
    A = [[] for _ in range(n + m)]
    # For each cell in the grid
    for i in range(n):
        for j, char in enumerate(input().rstrip()):
            if char == "1":
                # Group by diagonal (i + j)
                A[i + j].append(i)

    ans = 0
    # Process two groups: even and odd diagonals
    for beg in range(2):
        S = []
        # Iterate through diagonals starting from beg
        for sm in range(beg, n + m, 2):
            # For each row in current diagonal group
            for i in A[sm]:
                # Calculate difference for interval representation
                diff = sm - 2 * i
                # Find where to insert in sorted list
                idx = bisect_left(S, diff)
                # If interval overlaps, update it
                if idx < len(S):
                    S[idx] = diff
                # Else add new interval
                else:
                    S.append(diff)
        # Count number of intervals (paths)
        ans += len(S)

    return ans


T = int(input())
out = [solve() for _ in range(T)]
print("\n".join(map(str, out)))


# https://github.com/VaHiX/CodeForces/