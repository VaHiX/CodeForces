# Problem: CF 2055 B - Crafting
# https://codeforces.com/contest/2055/problem/B

"""
B. Crafting

Algorithm:
- For each test case, we are given initial amounts `a` and required amounts `b` of n materials.
- We can perform an operation: select a material i, spend 1 unit of all other materials to gain 1 unit of material i.
- The key insight is that this operation essentially allows us to "transfer" resources from all other materials to one chosen material.
- To determine if we can craft the artifact:
    - Let `d[i] = a[i] - b[i]` for all i. These are the excess or deficit of each material.
    - If `sum(d) < 0`, it's impossible because we don't have enough total units.
    - Otherwise, we can redistribute the materials to meet the requirement.
    - The critical check is that after redistribution, we must be able to satisfy all requirements.
    - A useful approach: take the two smallest values in `d` (sorted), and their sum should be non-negative.
        This ensures that even if we transfer resources optimally, we are not short of required units.

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing the differences
"""

import sys

input = sys.stdin.readline
t = int(input())
for _ in range(t):
    input()  # Read empty line
    l = zip(map(int, input().split()), map(int, input().split()))
    # Calculate difference between available and required amounts for each material
    diff = sorted(x - y for x, y in l)
    # Check if the sum of two smallest differences is non-negative
    print("YES" if sum(diff[:2]) >= 0 else "NO")


# https://github.com/VaHiX/codeForces/