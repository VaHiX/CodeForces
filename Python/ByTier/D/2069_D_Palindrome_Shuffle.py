# Problem: CF 2069 D - Palindrome Shuffle
# https://codeforces.com/contest/2069/problem/D

"""
D. Palindrome Shuffle

Purpose:
This code determines the minimum length of a contiguous substring that needs to be shuffled to convert a given string into a palindrome.
The algorithm works by:
1. Finding the first and last mismatched characters in the string.
2. Analyzing the substring between these mismatches to determine minimal shuffle needed.
3. Optimizing by checking both sides (left-to-right and right-to-left) to find the smallest subsegment to shuffle.

Algorithms/Techniques:
- Two-pointer technique to find mismatched positions
- Frequency counting for character analysis
- Greedy approach to minimize the shuffle length

Time Complexity: O(n) where n is the length of the string. Each character is processed a constant number of times.
Space Complexity: O(1) as we use only fixed-size arrays (26 characters for lowercase letters).
"""

import sys

input = sys.stdin.readline


def ii():
    return input().rstrip()


def N():
    return int(input())


def I():
    return map(int, input().split())


def L():
    return list(map(int, input().split()))


def solve():
    s = ii()
    n = len(s)
    for i in range(n):
        if s[i] != s[n - i - 1]:
            l, r = i, n - i
            break
    else:
        print(0)
        return
    s = s[l:r]
    n = len(s)
    f = [0] * 26
    for c in s:
        f[ord(c) - 97] += 1
    nf = [0] * 26
    for i in range(n // 2):
        c = ord(s[i]) - 97
        nf[c] += 1
        if 2 * nf[c] > f[c]:
            ans = n - i
            break
    else:
        for i in range(n // 2 - 1, -1, -1):
            if s[i] != s[n - i - 1]:
                print(i + 1)
                return
    nf = [0] * 26
    for i in range(n // 2):
        c = ord(s[n - i - 1]) - 97
        nf[c] += 1
        if 2 * nf[c] > f[c]:
            ans = min(ans, n - i)
            break
    print(ans)


for _ in range(N()):
    solve()


# https://github.com/VaHiX/codeForces/