# Problem: CF 1824 A - LuoTianyi and the Show
# https://codeforces.com/contest/1824/problem/A

"""
Problem: LuoTianyi and the Show

Algorithm:
This problem involves simulating seat occupancy under specific rules for seating:
- Person -1: sits at the leftmost available seat next to the leftmost occupied seat (or leaves if seat 1 is taken)
- Person -2: sits at the rightmost available seat next to the rightmost occupied seat (or leaves if seat m is taken)
- Person x > 0: sits at seat x if available, otherwise leaves

Approach:
We simulate different seating orders using greedy strategy:
1. Count prefix (-2) and suffix (-1) people
2. For each valid seating order that maximizes total people seated:
   - Simulate adding existing people to seats
   - For each possible insertion point, calculate how many additional people can be seated
   - Track maximum

Time Complexity: O(n * m) per test case in worst case
Space Complexity: O(m) for storing seat states and counters

"""

import sys

input = sys.stdin.buffer.readline


def process(m, A):
    len(A)
    seats = [0 for i in range(m + 1)]  # Track which seats are occupied (1-indexed)
    suffix = 0  # Count of -1 type people (occupy leftmost available from right)
    prefix = 0  # Count of -2 type people (occupy rightmost available from left)
    for x in A:
        if x == -1:
            suffix += 1
        elif x == -2:
            prefix += 1
        else:
            seats[x] = 1  # Mark seat x as occupied
    S = sum(seats)  # Number of fixed-seat people (x > 0)
    if S == 0:
        # No one has a fixed seat, so we can place at most min(m, max(prefix, suffix))
        answer = min(m, max(prefix, suffix))
    else:
        before = 0
        # Initial estimate assuming prefix and suffix people are placed among existing seats
        answer = min(m, max(prefix + S, suffix + S))
        for i in range(1, m + 1):
            if seats[i] == 1:
                before += 1
                after = S - before  # People fixed to the right of current position
                left_side = min(i, before + suffix)  # Max people that can be placed to the left (including prefix and suffix)
                right_side = min(m - i, after + prefix)  # Max people that can be placed to the right (including prefix and suffix)
                answer = max(answer, left_side + right_side)
    sys.stdout.write(f"{answer}\n")
    return


t = int(input())
for i in range(t):
    n, m = [int(x) for x in input().split()]
    A = [int(x) for x in input().split()]
    process(m, A)


# https://github.com/VaHiX/codeForces/