# Problem: CF 1976 D - Invertible Bracket Sequences
# https://codeforces.com/contest/1976/problem/D

"""
Algorithm: 
- Use a balance counter to track the depth of brackets.
- Maintain a list `c` where `c[i]` counts how many times we have reached depth `i`.
- For each character in the string:
  - If we are at depth `cnt`, we can form valid pairs with previous occurrences at that depth.
  - Update counts accordingly as we traverse.
- Time Complexity: O(n) per test case
- Space Complexity: O(n) for the list `c`

Techniques:
- Balance tracking
- Prefix sum-like counting with cumulative updates
"""

from bisect import *
from collections import *
from itertools import *
from math import *
from sys import *

input = lambda: stdin.readline().strip()


def I():
    return input()


def II():
    return int(input())


def FI():
    return float(input())


def MII():
    return map(int, input().split())


def MFI():
    return map(float, input().split())


def L():
    return list(input())


def LI():
    return list(input().split())


def LII():
    return [*map(int, input().split())]


def LFI():
    return [*map(float, input().split())]


for _ in range(II()):
    s = L()
    ln = len(s)
    c = [0] * ln
    ans = 0
    cnt = 0
    for x in s:

        ans += c[cnt]  # Add number of previous positions at same depth
        c[cnt] += 1    # Increment count at current depth
        if cnt:        # If we're not at depth 0
            c[(cnt - 1) // 2] = 0  # Reset the counter for the parent depth
        if x == "(":
            cnt += 1   # Increase depth
        else:
            cnt -= 1   # Decrease depth

    print(ans)


# https://github.com/VaHiX/CodeForces/