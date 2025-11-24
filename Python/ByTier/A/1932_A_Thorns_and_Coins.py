# Problem: CF 1932 A - Thorns and Coins
# https://codeforces.com/contest/1932/problem/A

"""
Code Purpose:
This code solves the problem of finding the maximum number of coins that can be collected
while traversing a path with thorns and coins. It uses a greedy approach by counting
all coins in the string, but only counts coins before the first occurrence of "**",
since that indicates an impossible move (two consecutive thorns) and we can't pass through them.
This is essentially a simplified version of dynamic programming or greedy algorithm.

Algorithms/Techniques:
- Greedy approach with string manipulation
- Linear scanning of the string to find first occurrence of "**"

Time Complexity:
O(n) where n is the length of the string, because we scan the string once to find the first "**"
and then count all "@" characters.

Space Complexity:
O(1) as we only use a constant amount of extra space.
"""

import sys

input = sys.stdin.readline


def inp():
    return int(input())


def inlt():
    return list(map(int, input().split()))


def insr():
    s = input()
    return s


def invr():
    return map(int, input().split())


n = inp()
for i in range(n):
    len_path = inp()
    s = insr()
    try:
        # Count coins before first occurrence of "**" - since we cannot pass through two consecutive thorns
        x = s[0 : s.index("**")].count("@")
    except ValueError:
        # If there are no "**" in the string, count all coins
        x = s.count("@")
    print(x)


# https://github.com/VaHiX/CodeForces/