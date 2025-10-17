# Problem: CF 2150 A - Incremental Path
# https://codeforces.com/contest/2150/problem/A

"""
A. Incremental Path

Problem Description:
We are given a strip of 10^9 cells, initially some cells are black and others are white.
For each person (from 1 to n), we execute a sequence of commands starting from cell 1.
Commands:
- 'A': move to next cell (x+1)
- 'B': move to the next white cell after x

Each person colors the final cell they land on black.
We track all cells that are black at the end and print them sorted.

Algorithms/Techniques:
- Simulation with tracking of black cells in a boolean array.
- Efficient handling of 'B' command by skipping to next white cell.
- Optimized range for tracking based on max(n, m) to prevent memory overflow.

Time Complexity: O(n * max(n, m)) where n is number of commands and m is number of initial black cells
Space Complexity: O(max(n, m)) for storing the black cell status array

Input:
Multiple test cases. Each test case includes:
- n (commands), m (initial black cells)
- String s of length n with commands 'A' and 'B'
- List of m initial black cell indices

Output:
For each test case:
- k: number of final black cells
- k space-separated black cell indices in increasing order
"""

import sys
from collections import *
from copy import *
from math import *


def in_ipynb():
    try:
        cfg = get_ipython().config
        if cfg["IPKernelApp"]["parent_appname"]:
            return True
        else:
            return False
    except NameError:
        return False


in_prac = in_ipynb()
fastio = 0
if in_prac:
    handle = open("cfinput.txt", "r")


def input():
    if in_prac:
        return handle.readline().rstrip("\r").rstrip("\n")
    else:
        return sys.stdin.readline().rstrip("\r").rstrip("\n")


def pr(output):
    sys.stdout.write(str(output) + "\n")
    return


if in_prac:
    handle = open("cfinput.txt", "r")
for _ in range(int(input())):
    n, m = map(int, input().split())
    M = max(m, n)
    s = input()
    l = list(map(int, input().split()))
    # Track all black cells up to a safe limit
    is_black = [0 for i in range(4 * M + 9)]
    # Mark initial black cells
    for i in l:
        if i <= 4 * M + 8:
            is_black[i] = 1
    pos = 1
    # Simulate each person's commands
    for i, op in enumerate(s):
        if op == "A":
            pos += 1
            is_black[pos] = 1
        else:
            # Move to next white cell
            pos += 1
            while is_black[pos]:
                pos += 1
            is_black[pos] = 1
            # Skip over any black cells until next white one
            while is_black[pos]:
                pos += 1
    final = []
    # Include cells beyond the safe limit that were initially black
    for i in l:
        if i > 4 * M + 8:
            final.append(i)
    # Collect all black cells from tracked area
    for i in range(4 * M + 9):
        if is_black[i]:
            final.append(i)
    final.sort()
    print(len(final))
    print(*final)



# https://github.com/VaHiX/CodeForces/