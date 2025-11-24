# Problem: CF 2094 D - Tung Tung Sahur
# https://codeforces.com/contest/2094/problem/D

"""
Problem: Determine if a recorded sound string `s` could have been generated from a pattern string `p` 
         where each character in `p` can be either one or two hits (L => L or LL, R => R or RR).

Algorithms/Techniques:
- Group consecutive identical characters using `itertools.groupby`.
- Compare the group sizes of `p` and `s`, ensuring that each group in `s` has a size 
  between the corresponding group in `p` and twice that size.

Time Complexity: O(n) where n is the total length of all strings processed.
Space Complexity: O(n) for storing grouped lengths.

"""

import sys

input = sys.stdin.readline
from itertools import groupby

ii = lambda: int(input())


def solve():
    p, s = input(), input()
    # Group consecutive same characters and record their counts
    arr_p = [len([*b]) for a, b in groupby(p)]
    arr_s = [len([*b]) for a, b in groupby(s)]
    
    # If first characters differ or number of groups differ, impossible
    if p[0] != s[0] or len(arr_p) != len(arr_s):
        print("NO")
        return 0
    
    # For each group, check that its size in s is between size in p and twice the size in p
    if all(a <= b <= a * 2 for a, b in zip(arr_p, arr_s)):
        print("YES")
    else:
        print("NO")


for _ in range(ii()):
    solve()


# https://github.com/VaHiX/codeForces/