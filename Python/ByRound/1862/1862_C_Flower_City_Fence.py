# Problem: CF 1862 C - Flower City Fence
# https://codeforces.com/contest/1862/problem/C

"""
Flower City Fence Problem

Purpose:
This code determines if a fence made of planks with decreasing heights is symmetrical when laid horizontally.
The fence is symmetrical if the original sequence of plank heights matches the horizontal layout sequence.
The horizontal layout is determined by how many planks are taller than or equal to each height.

Algorithms/Techniques:
- Greedy approach with symmetry checking
- For each plank at position i with height h, we check if h-th plank from the start
  maps correctly to position i in the horizontal layout.

Time Complexity: O(n) where n is the number of planks.
Space Complexity: O(1) excluding input storage.

The key insight:
If the original array is [a0, a1, ..., a_{n-1}] and we lay it horizontally,
then the horizontal array will be [b0, b1, ..., b_{n-1}] where bi is the number of elements >= i+1 in original.
We determine symmetry by checking if this mapping preserves the original structure.
"""

import sys

input = sys.stdin.readline
t = int(input())
for _ in range(t):
    n = int(input())
    nums = list(map(int, input().split()))
    if nums[0] != len(nums):
        print("NO")
        continue
    symmetrical = True
    for i in range(n):
        # Check if the position mapping is correct for symmetry
        # nums[nums[i] - 1] gives the height at position nums[i]-1 in zero-indexed terms
        # i is the current index
        # If this condition fails, symmetry is broken
        if nums[nums[i] - 1] - i:
            continue
        else:
            symmetrical = False
            break
    print(["NO", "YES"][symmetrical])


# https://github.com/VaHiX/CodeForces/