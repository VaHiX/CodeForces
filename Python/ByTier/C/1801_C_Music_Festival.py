# Problem: CF 1801 C - Music Festival
# https://codeforces.com/contest/1801/problem/C

"""
Algorithm: Dynamic Programming with Binary Search
Purpose: Maximize the number of tracks that are cooler than all previously listened tracks.
Time Complexity: O(n * k * log(n * k)) where n is number of albums and k is average number of tracks.
Space Complexity: O(n * k) for storing arrays and DP structure.

The algorithm works by:
1. Preprocessing each album to keep only tracks that are strictly increasing (only keeping the track if it's greater than previous)
2. Sorting albums by their maximum track value
3. Using dynamic programming with binary search to merge tracks in order, keeping track of the best sequence
"""

import sys

input = sys.stdin.buffer.readline

T = int(input())


def bisect(arr, x):
    # Binary search to find the position where x should be inserted to maintain sorted order
    l = 0
    r = len(arr)
    while r - l > 0:
        m = (l + r) // 2
        if arr[m] <= x:
            r = m
        else:
            l = m + 1
    return l


for _t in range(T):
    n = int(input())

    arrs = []
    arr_maxs = []
    for i in range(n):
        k_i = input()
        arr = []
        for x in input().split():
            x = int(x)

            # Only keep tracks that are greater than the last one (strictly increasing)
            if len(arr) > 0 and x <= arr[-1]:
                continue
            arr.append(x)

        arrs.append(arr)
        arr_maxs.append(arr[-1])

    # Sort albums by max track value to process them in order
    o_arrs = sorted(list(range(n)), key=lambda i: arr_maxs[i])

    dp = []
    for i in o_arrs[::-1]:
        arr = arrs[i]
        max_v = arr[-1]
        # Find where to insert the max value of current album in dp array
        l = bisect(dp, max_v)

        # Update the dp array with current album's tracks
        for j in range(len(arr)):
            v = arr[-1 - j]
            if l + j >= len(dp):
                dp.append(v)
            else:
                dp[l + j] = max(dp[l + j], v)

    print(len(dp))


# https://github.com/VaHiX/CodeForces/