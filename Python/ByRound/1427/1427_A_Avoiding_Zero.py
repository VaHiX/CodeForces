# Problem: CF 1427 A - Avoiding Zero
# https://codeforces.com/contest/1427/problem/A

"""
Code Purpose:
This code solves the "Avoiding Zero" problem where we need to rearrange an array such that all prefix sums are non-zero.
The strategy is based on the total sum of the array:
- If the sum is 0, it's impossible to avoid zero prefix sums (because the final sum must be 0, and at some point we must hit 0).
- If the sum is positive, sorting in descending order ensures that prefix sums remain positive.
- If the sum is negative, sorting in ascending order ensures that prefix sums remain negative.

Algorithms/Techniques:
Greedy approach with sorting.
Time Complexity: O(n log n) per test case due to sorting.
Space Complexity: O(n) for storing the input and output arrays.
"""

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n = int(input())
    data = list(map(int, input().split()))
    if sum(data) == 0:
        # If the total sum is zero, it's impossible to avoid zero prefix sums
        print("NO")
    elif sum(data) < 0:
        # If the sum is negative, sort in ascending order to keep prefix sums negative
        print("YES")
        print(*sorted(data))
    else:
        # If the sum is positive, sort in descending order to keep prefix sums positive
        print("YES")
        print(*sorted(data, reverse=True))


# https://github.com/VaHiX/CodeForces/