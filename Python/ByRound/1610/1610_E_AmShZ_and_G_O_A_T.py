# Problem: CF 1610 E - AmShZ and G.O.A.T.
# https://codeforces.com/contest/1610/problem/E

"""
Purpose: This code solves the problem of finding the minimum number of elements to delete from an array to make it "good".
A "good" array has no subsequence that is "terrible". A "terrible" array has more elements greater than average than elements less than average (excluding elements equal to average).

Algorithms/Techniques:
- Sorting the array to simplify processing
- Two-pointer technique with binary search (bisect_left)
- Greedy approach to maximize the size of good subarray

Time Complexity: O(n log n) per test case due to sorting and binary search operations.
Space Complexity: O(n) for storing the array and auxiliary variables.
"""

import sys

input = sys.stdin.readline
from bisect import bisect_left

for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    a.sort()  # Sort the array to enable efficient processing
    sol = 0  # Stores the maximum size of a good subarray
    c = 0  # Pointer to traverse the array
    while c < n:
        elm = a[c]  # Current element value
        f = 0  # Count of current element
        while c < n and a[c] == elm:
            f += 1
            c += 1  # Count all occurrences of current element
        nxt = c - 1  # Pointer to next element
        total = 0
        while nxt < n:
            # Find the smallest index where 2 * a[nxt] - elm is located
            q = max(bisect_left(a, 2 * a[nxt] - elm), nxt + 1)
            if q < n:
                f += 1  # Increment count if valid index found
            nxt = q  # Move pointer
        sol = max(sol, f)  # Update max size of good subarray
    print(n - sol)  # Minimum deletions = total length - max good subarray length


# https://github.com/VaHiX/CodeForces/