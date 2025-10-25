# Problem: CF 1918 A - Brick Wall
# https://codeforces.com/contest/1918/problem/A

"""
Code Purpose:
This code solves the problem of finding the maximum stability of a brick wall of size n×m.
Each brick is of size 1×k where k ≥ 2, and can be placed either horizontally or vertically.
Stability is defined as the difference between the number of horizontal bricks and vertical bricks.
The optimal strategy is to use as many horizontal bricks as possible to maximize stability,
since horizontal bricks contribute +1 to stability while vertical bricks contribute -1.
The idea is to place horizontal 1×k bricks optimally to cover all rows, and count how many
such bricks can fit in each row, then multiply by the number of rows.

Algorithms/Techniques:
- Greedy approach: maximize number of horizontal bricks
- Mathematical calculation: For each row, the maximum number of horizontal 1×k bricks (k≥2)
  is floor(m / 2) because each such brick covers at least 2 cells horizontally.
- For n rows, total horizontal bricks = n * floor(m / 2)
- Vertical bricks needed = 0 (if all rows are filled optimally with horizontal bricks)
- So the maximum stability = total horizontal bricks - total vertical bricks = n * (m // 2) - 0 = n * (m // 2)

Time Complexity: O(1) per test case
Space Complexity: O(1)
"""

import sys

input = sys.stdin.readline
sys.setrecursionlimit(5 * 10**4)


def readList():
    return list(map(int, input().split()))


def readInt():
    return int(input())


def readInts():
    return map(int, input().split())


def readStr():
    return input().strip()


def solve():
    n, m = readInts()
    return n * (m // 2)  # Maximum stability is achieved by placing as many horizontal bricks as possible.


for _ in range(int(input())):
    print(solve())


# https://github.com/VaHiX/CodeForces/