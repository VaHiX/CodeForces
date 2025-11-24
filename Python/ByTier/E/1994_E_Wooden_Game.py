# Problem: CF 1994 E - Wooden Game
# https://codeforces.com/contest/1994/problem/E

"""
Problem: Wooden Game
Algorithm: Greedy with Bitwise Operations
Time Complexity: O(n) per test case, where n is the total number of nodes across all trees
Space Complexity: O(1)

The solution works by:
1. For each tree, we track the cumulative OR of all subtree sizes seen so far (res).
2. We also track the maximum bitwise AND of the current res and the size of the current tree (best).
3. At the end, we add the largest power of 2 that fits in the bit length of best to maximize the final OR result.

This greedy approach leverages the fact that the bitwise OR operation is monotonic and adding larger powers of two helps achieve higher OR values.
"""

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    res = 0           # cumulative OR of subtree sizes
    best = 0          # maximum bitwise AND of res and current tree size
    for _ in range(int(input())):  # iterate over each tree
        n = int(input())           # size of current tree
        _ = input()                 # read parent info (not used in logic)
        share = res & n            # bitwise AND of res and n
        if share > best:           # update best if this AND is larger
            best = share
        res |= n                   # update res with OR of n
    print(res | ((1 << best.bit_length()) - 1))  # output final result with optimized OR


# https://github.com/VaHiX/CodeForces/