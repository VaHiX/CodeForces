# Problem: CF 1923 D - Slimes
# https://codeforces.com/contest/1923/problem/D

"""
Algorithm: Slime Eating Process
Approach: 
1. Preprocess the array to compute prefix sums for quick range sum queries.
2. For each slime, determine the minimum time it takes to be eaten by considering:
   - Left and right neighbor comparisons
   - Use of prefix sums and binary search to efficiently find the earliest possible eater
3. Process from left and right to calculate minimum eating times for each slime.

Time Complexity: O(n log n) per test case due to prefix sums and binary search operations
Space Complexity: O(n) for storing prefix sums and auxiliary arrays
"""

import sys
from bisect import *
from itertools import accumulate

input = lambda: sys.stdin.readline().rstrip()
sint = lambda: int(input())
mint = lambda: map(int, input().split())
ints = lambda: list(map(int, input().split()))


def solve() -> None:
    n = sint()
    nums = ints()
    ans = [-1] * n
    pres = list(accumulate(nums, initial=0))  # Prefix sum array
    left = [-1] * n  # left[i] stores the closest left neighbor with smaller value
    
    # Build left array for each position
    for i in range(1, n):
        if nums[i] == nums[i - 1]:
            left[i] = left[i - 1]  # Same value, inherit from previous
        else:
            left[i] = i - 1  # Previous element is smaller
        # Check if current slime can be eaten by its left neighbor in 1 second
        if nums[i] < nums[i - 1]:
            ans[i] = 1
        # If current slime can't be eaten directly by left neighbor
        elif (
            nums[i] >= pres[i]  # Current slime is larger or equal to prefix sum up to i
            or left[i] == -1  # No valid left neighbor
            or (left[i] == i - 1 and left[i - 1] == -1)  # No valid left left neighbor
        ):
            continue  # Skip further processing
        elif left[i] < i - 1 and pres[i] - pres[left[i]] > nums[i]:  # Range sum > current slime
            ans[i] = i - left[i]  # Time = distance to left neighbor
        elif left[i] == i - 1 and pres[i] - pres[left[i - 1]] > nums[i]:  # Special case
            ans[i] = i - left[i - 1]
        else:
            # Binary search for the required position
            k = bisect_left(pres, pres[i] - nums[i])  # Find first position with sum <= (pres[i] - nums[i])
            ans[i] = i - k + 1  # Time to reach that position

    right = [n] * n  # right[i] stores the closest right neighbor with smaller value
    # Build right array for each position
    for i in range(n - 2, -1, -1):
        if nums[i] == nums[i + 1]:
            right[i] = right[i + 1]  # Same value, inherit from next
        else:
            right[i] = i + 1  # Next element is smaller
        # Check if current slime can be eaten by its right neighbor in 1 second
        if nums[i] < nums[i + 1]:
            ans[i] = 1
        # If current slime can't be eaten directly by right neighbor
        elif (
            nums[i] >= pres[-1] - pres[i + 1]  # Current slime is larger or equal to suffix sum
            or right[i] == n  # No valid right neighbor
            or (right[i] == i + 1 and right[i + 1] == n)  # No valid right right neighbor
        ):
            continue  # Skip further processing
        elif right[i] > i + 1 and pres[right[i] + 1] - pres[i + 1] > nums[i]:  # Range sum > current slime
            if ans[i] == -1 or right[i] - i < ans[i]:  # Update if better time found
                ans[i] = right[i] - i
        elif right[i] == i + 1 and pres[right[i + 1] + 1] - pres[i + 1] > nums[i]:  # Special case
            if ans[i] == -1 or right[i + 1] - i < ans[i]:
                ans[i] = right[i + 1] - i
        else:
            # Binary search for the required position
            k = bisect(pres, pres[i + 1] + nums[i])  # Find first position with sum > (pres[i+1] + nums[i])
            if ans[i] == -1 or k - i - 1 < ans[i]:  # Update if better time found
                ans[i] = k - i - 1

    print(*ans)


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/