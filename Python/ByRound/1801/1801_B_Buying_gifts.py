# Problem: CF 1801 B - Buying gifts
# https://codeforces.com/contest/1801/problem/B

"""
Algorithm: Minimize the absolute difference between maximum prices of gifts bought for two friends
Approach:
1. For each department, we have two choices: buy from store 1 (cost a[i]) or store 2 (cost b[i]).
2. We want to assign each department to one of the two stores such that the difference between max prices for friend 1 and friend 2 is minimized.
3. This can be solved using binary search on sorted arrays to find optimal assignment.

Time Complexity: O(n * log n) due to sorting and binary search operations
Space Complexity: O(n) for storing the store data and auxiliary arrays

Key Techniques:
- Sorting departments by first store price in descending order
- Binary search to efficiently find closest elements
- Greedy assignment with tracking of running maximums
"""

import bisect
import sys

input = sys.stdin.readline
t = int(input())
for cases in range(t):
    n = int(input())
    b = [0 for _ in range(n)]
    store = [0 for _ in range(n)]
    for i in range(n):
        x, y = map(int, input().split(" "))
        store[i] = (x, y)  # Store prices for department i
        b[i] = y  # Store second store prices for sorting
    store.sort(reverse=True)  # Sort by first store price descending
    b.sort()  # Sort second store prices
    max_before = -1
    min_so_far = max(b[-1], store[-1][0]) + 1  # Initialize with a large value

    for i in range(n):

        max_first = store[i][0]  # Price of first store in current department
        left_ins = bisect.bisect_left(b, max_first)  # Find insertion point for max_first
        if left_ins < n and b[left_ins] == store[i][1]:  # Adjust if exact match
            left_ins += 1
        closest_expensiver = b[left_ins] if left_ins < n else -1  # Next larger value
        right_ins = bisect.bisect_right(b, max_first) - 1  # Find insertion point from right
        if right_ins < n and b[right_ins] == store[i][1]:  # Adjust if exact match
            right_ins -= 1
        closest_cheaper = b[right_ins] if 0 <= right_ins < n else -1  # Previous smaller value
        max_second = max_before  # Current maximum second friend's gift cost
        if max_second != -1:
            min_so_far = min(min_so_far, abs(max_second - max_first))
        if closest_cheaper > max_second:
            min_so_far = min(min_so_far, abs(closest_cheaper - max_first))
        if closest_expensiver > max_second:
            min_so_far = min(min_so_far, abs(closest_expensiver - max_first))
        if max_before > max_first:
            break  # Optimization: early termination if order violated
        max_before = max(store[i][1], max_before)  # Update max second friend cost
    print(min_so_far)


# https://github.com/VaHiX/CodeForces/