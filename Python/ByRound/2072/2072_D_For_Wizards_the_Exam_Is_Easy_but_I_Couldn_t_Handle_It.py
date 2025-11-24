# Problem: CF 2072 D - For Wizards, the Exam Is Easy, but I Couldn't Handle It
# https://codeforces.com/contest/2072/problem/D

"""
D. For Wizards, the Exam Is Easy, but I Couldn't Handle It
Algorithm: Brute-force over all subarrays [l, r] and simulate the left cyclic shift,
           then count inversions in the resulting array to find the minimum.

Time Complexity: O(n^3) per test case due to:
                 - O(n^2) for choosing subarray [l, r]
                 - O(n) for simulating the shift and counting inversions
Space Complexity: O(n) for storing the array and temporary arrays

Note: This brute-force approach works within the constraints (n <= 2000)
      since total operations across all test cases is bounded by 4*10^6.
"""

import sys

input = sys.stdin.readline
t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    ma = 0  # Tracks the maximum "net gain" in inversions (negative means reduction)
    ans = (1, 1)  # Best subarray indices to apply the spell
    for i in range(n):
        now = 0  # Current inversion count difference for this subarray
        for j in range(i + 1, n):
            if a[i] > a[j]:
                now += 1  # a[i] contributes to an inversion with a[j]
            elif a[i] < a[j]:
                now -= 1  # a[i] reduces inversion count with a[j]
            if ma < now:  # We want to minimize the number of inversions
                ma = now
                ans = (i + 1, j + 1)  # Convert to 1-based indexing
    print(*ans)


# https://github.com/VaHiX/codeForces/