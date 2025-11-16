# Problem: CF 2163 D2 - Diadrash (Hard Version)
# https://codeforces.com/contest/2163/problem/D2

"""
Algorithm: Binary search on the answer to find the maximum MEX among all ranges.
We use the fact that for a range [l, r], MEX is the smallest non-negative integer not present in the range.
We first identify which ranges are relevant for max MEX calculation and then binary search on the valid ranges.

Time Complexity: O(q log q + q) where q is number of ranges
Space Complexity: O(q) for storing the ranges and auxiliary arrays

This approach uses binary search to efficiently locate the maximum MEX value among all query ranges.
"""

import sys

input = sys.stdin.readline

t = int(input())

for tests in range(t):
    n, q = map(int, input().split())
    Q = [list(map(int, input().split())) for i in range(q)]

    # X[i] stores the maximum endpoint for ranges starting at i
    X = [-1] * (n + 1)

    # For each range, update the maximum endpoint for its start point
    for x, y in Q:
        if X[x] < y:
            X[x] = y

    # Filter out ranges that are dominated by others - keep only the rightmost range for each start
    MAX = 0
    for i in range(1, n + 1):
        if X[i] == -1:
            continue
        if X[i] <= MAX:
            X[i] = -1  # This range is dominated by a previous one
        MAX = max(MAX, X[i])

    # Create a list of valid ranges (start, end) pairs
    QLIST = []
    for i in range(1, n + 1):
        if X[i] != -1:
            QLIST.append((i, X[i]))

    # Edge case: if no valid ranges, the maximum MEX is 0
    if len(QLIST) == 0:
        print("!", 0, flush=True)
        continue

    # Binary search to find the maximum MEX
    LEFT = 0
    RIGHT = len(QLIST) - 1

    MAX = 0

    # Continue binary search until we have only one candidate
    while RIGHT > LEFT:
        mid = (LEFT + RIGHT) // 2

        # Query two ranges: from left to mid and from mid+1 to right
        s = QLIST[LEFT][0]
        t = QLIST[mid][1]
        u = QLIST[mid + 1][0]
        v = QLIST[RIGHT][1]

        print("?", s, t, flush=True)
        ret = int(input())
        print("?", u, v, flush=True)
        ret2 = int(input())

        # Compare the MEX values and eliminate half based on comparison
        if ret > ret2:
            RIGHT = mid  # Left half contains better answer
        else:
            LEFT = mid + 1  # Right half contains better answer

    # Final query to get the exact maximum MEX in the identified range
    s = QLIST[LEFT][0]
    t = QLIST[LEFT][1]

    print("?", s, t, flush=True)
    ret = int(input())

    MAX = max(MAX, ret)

    print("!", MAX, flush=True)


# https://github.com/VaHiX/CodeForces/