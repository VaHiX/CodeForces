# Problem: CF 2021 B - Maximize Mex
# https://codeforces.com/contest/2021/problem/B

"""
B. Maximize Mex

Algorithm/Technique: Greedy + Array Manipulation

Time Complexity: O(N)
Space Complexity: O(N)

The problem asks to maximize the MEX (minimum excluded value) of an array by incrementing elements by x any number of times.
We use a frequency count approach to track how many times each value appears, and then simulate the process of "moving" values forward 
by x steps when there are duplicates, effectively allowing us to fill gaps in the sequence.

Key steps:
1. Count frequencies of all elements <= N (since MEX can't exceed N+1).
2. Iterate through possible indices and try to "shift" excess counts by x steps.
3. Find the first index where count is 0 — that's our answer.
"""

import sys

input = sys.stdin.readline
F = lambda: [*map(int, input().split())]
for _ in range(int(input())):
    N, X = F()
    A = F()
    CNT = [0] * (N + 2)  # Frequency array to count occurrences up to N+1
    for a in A:
        if a <= N:  # Only consider elements within reasonable bounds
            CNT[a] += 1
    for i in range(N + 2):
        if CNT[i] == 0:  # First missing non-negative integer
            print(i)
            break
        if CNT[i] > 1 and i + X < N + 2:  # If duplicate and can shift to next position
            CNT[i + X] += CNT[i] - 1  # Move extra occurrences forward by X steps


# https://github.com/VaHiX/codeForces/