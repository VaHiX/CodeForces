# Problem: CF 1863 D - Two-Colored Dominoes
# https://codeforces.com/contest/1863/problem/D

"""
Two-Colored Dominoes

Algorithm:
- For each row, process from left to right and handle 'U' cells. 
  Each 'U' connects to the cell below it. Assign colors to these 
  pairs such that each pair has one black and one white cell.
- For each column, process from top to bottom and handle 'L' cells.
  Each 'L' connects to the cell to the right. Assign colors to these
  pairs such that each pair has one black and one white cell.
- If at any point we cannot assign a valid color to a pair (i.e., 
  the current state is inconsistent), return -1.
- Otherwise, return the color assignment.

Time Complexity: O(n * m) - Each cell is processed at most twice.
Space Complexity: O(n * m) - For storing the board and output.
"""

import sys

input = sys.stdin.readline


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
    arr = [readStr() for _ in range(n)]
    ans = [["."] * m for _ in range(n)]
    for i in range(n):
        curr = 0
        for j in range(m):
            if arr[i][j] == "U":
                # Assign colors to the current cell and the cell below
                ans[i][j] = "W" if not curr else "B"
                ans[i + 1][j] = "W" if curr else "B"
                curr ^= 1  # Flip the current state
        if curr:  # If there's an unmatched domino in the row, impossible to make it balanced
            return -1
    for j in range(m):
        curr = 0
        for i in range(n):
            if arr[i][j] == "L":
                # Assign colors to the current cell and the cell to the right
                ans[i][j] = "W" if not curr else "B"
                ans[i][j + 1] = "W" if curr else "B"
                curr ^= 1  # Flip the current state
        if curr:  # If there's an unmatched domino in the column, impossible to make it balanced
            return -1
    return "\n".join(["".join(each) for each in ans])


for _ in range(int(input())):
    print(solve())


# https://github.com/VaHiX/CodeForces/