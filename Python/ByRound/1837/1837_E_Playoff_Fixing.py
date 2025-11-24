# Problem: CF 1837 E - Playoff Fixing
# https://codeforces.com/contest/1837/problem/E

"""
Code Purpose:
This code solves the problem of determining how many valid ways there are to assign seeds to teams in a playoff tournament such that the final placements of teams match a given specification. It uses a recursive-like approach by simulating the tournament rounds and tracking valid seed assignments.

Algorithms/Techniques:
- Simulation of tournament rounds
- Greedy assignment of seeds to maintain valid placements
- Modular arithmetic for large number handling
- Bit manipulation for pairing (i << 1, i << 1 | 1)

Time Complexity: O(2^k), where k is the input parameter. There are 2^k teams, and we process each level of the tournament once.
Space Complexity: O(2^k), to store the list of teams and intermediate results during simulation.
"""

import os
import sys

if os.path.exists("in.txt"):
    file = open("in.txt")
    input = file.readline
else:
    input = sys.stdin.readline

readi = lambda: int(input())
readis = lambda: list(map(int, input().split()))
reads = lambda: input().rstrip()
readss = lambda: input().split()
mod = 998244353


def solution():
    k, a = readi(), readis()
    res = 1
    while True:
        if len(a) <= 2:
            if a == [-1, -1]:
                res = res * 2 % mod
            print(res)
            return
        n = len(a)
        m = n // 2
        b = [0] * m

        c = 0
        for i in range(m):  # Iterate through pairs of teams
            x, y = a[i << 1], a[i << 1 | 1]  # Get pair members using bit shift
            if x > y:  # Ensure x is smaller (stronger team)
                x, y = y, x
            if x == y == -1:  # Both teams unassigned
                b[i] = -1
                c += 1
                res = res * c * 2 % mod  # 2 choices for the pair, c combinations
            elif x == -1:  # Only x unassigned
                if y > m:  # y is a winner from a later round - invalid to assign
                    b[i] = -1
                else:
                    b[i] = y
                    c += 1
                    res = res * c % mod  # c choices for assignment
            else:  # Both teams assigned
                if x > m or y <= m:  # Invalid assignment due to placement rules
                    print(0)
                    return
                b[i] = x  # Winner is x (stronger team)
        a = b  # Move to next round
    print(res)


for i in range(1):
    solution()


# https://github.com/VaHiX/CodeForces/