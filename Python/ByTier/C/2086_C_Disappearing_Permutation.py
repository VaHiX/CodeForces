# Problem: CF 2086 C - Disappearing Permutation
# https://codeforces.com/contest/2086/problem/C

"""
C. Disappearing Permutation
Algorithm: Simulation with Path Compression
Time Complexity: O(n) amortized per test case
Space Complexity: O(n)

The problem involves processing a sequence of queries where elements of a permutation are set to 0 one by one.
For each query, we need to determine the minimum number of operations to restore the array to a valid permutation.

Each operation allows replacing an element in the array with a value from 1 to n.
We simulate the process by tracking how many times each element must be "moved" in order to be placed at its correct position,
using path compression to optimize the traversal.

The approach simulates the movement of elements as they are replaced with 0, counting the number of operations needed.
"""

import sys

input = lambda: sys.stdin.readline().rstrip()
for _ in range(int(input())):
    n = int(input())
    p = list(map(int, input().split()))
    ew, t = [], 0
    for i in map(int, input().split()):
        c, x = 0, i
        # Traverse the path from x to the final position using path compression
        while p[x - 1] != 0:
            y = x - 1
            x, p[y] = p[x - 1], 0  # Move element and mark current position as 0
            c += 1
        t += c
        ew.append(t)
    print(" ".join(map(str, ew)))


# https://github.com/VaHiX/codeForces/