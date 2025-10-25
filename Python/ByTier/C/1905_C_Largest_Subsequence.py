# Problem: CF 1905 C - Largest Subsequence
# https://codeforces.com/contest/1905/problem/C

"""
Code Purpose:
This code solves the problem of finding the minimum number of operations to sort a string
by repeatedly selecting the lexicographically largest subsequence and cyclically shifting it to the right.

Algorithm:
1. Identify the lexicographically largest subsequence by scanning from right to left,
   keeping track of characters that form a non-increasing sequence from the end.
2. Check if the string can be sorted by verifying that the characters can be matched
   with the subsequence while maintaining non-decreasing order.
3. If valid, return the number of operations equal to the length of the largest subsequence
   minus the count of the last character (to avoid over-counting).

Time Complexity: O(n) where n is the length of the string.
Space Complexity: O(n) for storing the 'big' array and flag array.
"""

import sys
from os import path

INF = 2**64 - 1
MOD = 10**9 + 7
YES = "Yes"
NO = "No"
if path.exists("input.txt"):
    sys.stdin = open("input.txt", "r")
input = lambda: sys.stdin.readline().rstrip()
si = lambda: int(input())
mi = lambda: map(int, input().split())
li = lambda: list(mi())


def solve(n, s):
    # Build the list 'big' of lexicographically largest subsequence from right to left
    big = [s[-1]]
    flag = [True] * n
    flag[-1] = False
    for i in range(n - 2, -1, -1):
        if s[i] >= big[-1]:
            big.append(s[i])
            flag[i] = False

    # Start comparison from the first character
    j = 0
    if flag[0] == True:
        pre = s[0]
    else:
        pre = big[0]
        j = 1

    # Check if the string can be sorted by matching the sequence with the subsequence
    for i in range(1, n):
        if flag[i] == True:
            # If this char belongs to the main string and not the subsequence
            if s[i] >= pre:
                pre = s[i]
                continue
            else:
                print(-1)
                return
        else:
            # If this char is part of the subsequence
            if big[j] >= pre:
                pre = big[j]
                j += 1
            else:
                print(-1)
                return

    # The number of operations is the size of the largest subsequence minus the count of the last element
    print(len(big) - big.count(big[-1]))
    return


caseNum = int(input())
for i in range(0, caseNum):
    n = int(input())
    s = input()
    solve(n, s)


# https://github.com/VaHiX/CodeForces/