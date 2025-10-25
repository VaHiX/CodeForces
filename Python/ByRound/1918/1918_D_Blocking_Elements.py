# Problem: CF 1918 D - Blocking Elements
# https://codeforces.com/contest/1918/problem/D

"""
Algorithm: Binary Search on Answer + Dynamic Programming with Sliding Window
Time Complexity: O(n * log(sum_of_array)) where n is the length of the array
Space Complexity: O(n) for prefix sum and dp arrays

This problem involves finding the minimum possible cost of blocking elements in an array.
The cost is defined as the maximum of:
1. Sum of all blocked elements
2. Maximum sum among segments formed when blocked elements are removed

We use binary search on the answer to find the minimum possible cost.
For each candidate cost, we check if it's achievable using a dynamic programming approach
with a sliding window technique to maintain valid segments.

The approach uses a deque to efficiently maintain a sliding window of indices,
where we track the minimal prefix sum for valid windows to compute the DP state.
"""

import sys
from collections import deque

sys.setrecursionlimit(2147483647)
input = sys.stdin.readline


def check(a, mid, s):
    """
    Check if it's possible to block elements such that the cost is <= mid.
    Parameters:
    a (list): The array of elements.
    mid (int): The current guessed cost.
    s (list): Prefix sum array of a.
    Returns:
    bool: True if possible to achieve cost <= mid, False otherwise.
    """
    n = len(a) - 1
    d = deque()
    dp = [0] * (n + 2)
    for i in range(n + 1):
        # Maintain decreasing order in deque (min at front)
        while len(d) > 0 and dp[d[-1]] >= dp[i]:
            d.pop()
        d.append(i)
        # Shrink window from left until sum is within limit
        while s[i] - s[d[0]] > mid:
            d.popleft()
        # Compute DP value for current index
        dp[i + 1] = dp[d[0]] + a[i]
    return dp[n + 1] <= mid


def solve():
    """
    Solve a single test case.
    """
    n = int(input())
    a = list(map(int, input().split())) + [0]
    s = [0] * (n + 2)
    for i in range(n + 1):
        s[i + 1] = s[i] + a[i]
    l, r = 1, sum(a)
    ans = r
    while l <= r:
        mid = (l + r) // 2
        if check(a, mid, s):
            ans = mid
            r = mid - 1
        else:
            l = mid + 1
    print(ans)


t = int(input())
for _ in range(t):
    solve()


# https://github.com/VaHiX/CodeForces/