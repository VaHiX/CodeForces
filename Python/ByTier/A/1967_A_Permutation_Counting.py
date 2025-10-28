# Problem: CF 1967 A - Permutation Counting
# https://codeforces.com/contest/1967/problem/A

"""
Problem: Permutation Counting
Algorithm: Binary search on the answer + greedy counting
Time Complexity: O(n * log(max_value)) where max_value ~ 10^12
Space Complexity: O(1)

The approach uses binary search to find the maximum number of cards of each type
we can have (let's call this value 'm') such that the total cost to reach this
state is <= k. Once we determine 'm', we compute the maximum score by:
1. Counting how many cards we need to buy (z = sum of (m - a[i]) for i in range(n))
2. Counting how many types have more than 'm' cards (t = count of a[i] > m)
3. The formula gives us the maximal score using these counts
"""

import sys

input = sys.stdin.readline


def fg():
    return int(input())


def fgh():
    return [int(xx) for xx in input().split()]


def tt():
    sys.stdout.flush()


def sd():
    print("Yes")


def df():
    print("No")


for __ in range(fg()):
    n, k = fgh()
    a = fgh()
    l = 0
    r = 10**12 + 1
    while r - l > 1:
        m = (l + r) // 2
        z = 0
        for i in range(n):
            z += max(0, m - a[i])  # Calculate total cards needed to make all types reach at least 'm'
        if z <= k:
            l = m  # If we can afford it, try higher
        else:
            r = m  # If we cannot afford it, try lower
    m = l
    z = 0
    t = 0
    for i in range(n):
        if a[i] > m:
            t += 1  # Count how many types exceed 'm'
        z += max(0, m - a[i])  # Total excess cards needed to make all types 'm'
    print((l - 1) * n + k - z + 1 + t)  # Final score computation


# https://github.com/VaHiX/CodeForces/