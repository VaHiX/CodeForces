# Problem: CF 1768 D - Lucky Permutation
# https://codeforces.com/contest/1768/problem/D

"""
Code Purpose:
This code solves the problem of finding the minimum number of swaps to transform a permutation into one with exactly one inversion.
It uses a cycle detection approach in permutations to determine how many swaps are needed to create exactly one inversion.

Algorithms/Techniques:
- Cycle decomposition in permutations
- Union-find like tracking with visited markers
- Greedy approach based on cycle lengths

Time Complexity: O(n)
Space Complexity: O(n)
"""

import sys

input = sys.stdin.readline


for _ in range(int(input())):
    n = int(input())
    w = [-1] + list(map(int, input().split()))  # 1-indexed permutation
    d = [0] * (n + 2)  # visited array, 1-indexed
    t, c = 1, 0  # t tracks if we're in a cycle with neighbors, c counts elements in current cycle
    for i in range(1, n + 1):
        if not d[i]:  # if not visited
            a = i
            c -= 1  # Start of a new cycle
            while not d[a]:  # Traverse the cycle
                d[a] = i  # Mark as visited in this cycle
                if t == 1:  # Check only in first step of current cycle
                    if d[a - 1] == i or d[a + 1] == i:  # If neighbor has same cycle id
                        t = -1  # Mark no valid neighbor found
                a = w[a]  # Move to next element in permutation
                c += 1  # Increment count of elements in cycle
    print(c + t)  # Adjust based on cycle properties to get min ops


# https://github.com/VaHiX/CodeForces/