# Problem: CF 2121 E - Sponsor of Your Problems
# https://codeforces.com/contest/2121/problem/E

"""
E. Sponsor of Your Problems

Purpose:
This code solves the problem of finding the minimum value of f(l,x) + f(x,r) for all integers x in the range [l, r],
where f(a,b) is the number of matching digits at corresponding positions in the decimal representations of a and b.

Algorithm:
The approach involves iteratively checking each prefix of l and r to determine how many positions match or can be matched by choosing an optimal x. For each prefix length i, we compute:
- 2 * (int(l[:i]) == int(r[:i])): if prefixes are equal, we get two matches in the final answer
- (int(l[:i]) + 1 == int(r[:i])): if l's prefix is one less than r's prefix, then we can potentially set x to have a prefix that makes both f(l,x) and f(x,r) maximize match count

Time Complexity: O(len(l)) per test case
Space Complexity: O(1)

Techniques:
- Prefix matching
- Greedy digit-by-digit comparison
"""

import sys

MOD = 1e9 + 7


def input():
    return sys.stdin.readline().strip()


t = int(input())
for tcs in range(t):
    l, r = input().split()
    res = 0
    for i in range(1, len(l) + 1):
        # Add contribution from matching prefixes
        res += 2 * (int(l[:i]) == int(r[:i]))  # If equal prefixes, both f(l,x) and f(x,r) can be maximized by choosing x appropriately
        # Check if l's prefix is exactly one less than r's prefix (allowing for a middle value x to bridge the gap)
        res += (int(l[:i]) + 1 == int(r[:i]))  # One valid choice of x exists that increases match count in both directions
    print(res)


# https://github.com/VaHiX/codeForces/