# Problem: CF 1843 E - Tracking Segments
# https://codeforces.com/contest/1843/problem/E

"""
Algorithm: Binary Search on Answer + Prefix Sum
Time Complexity: O((n + m + q) * log(q))
Space Complexity: O(n)

This solution uses binary search to find the minimum change number after which at least one segment becomes beautiful.
For each mid value in binary search, we simulate the array up to that point and use prefix sums to quickly compute
the difference between ones and zeros in each segment. A segment is beautiful if the count of ones > count of zeros.
"""

import sys


def rline():
    return sys.stdin.readline()


N = int(2e5)
l = [0] * (N + 1)
r = [0] * (N + 1)
x = [0] * (N + 1)
a = [0] * (N + 1)
t = int(rline())


def check(mid):
    # Reset array a to zeros
    for i in range(1, n + 1):
        a[i] = 0
    # Set elements to 1 based on first mid changes
    for i in range(1, mid + 1):
        a[x[i]] = 1
    # Build prefix sum array where each element is:
    # -1 if original element is 0
    # +1 if original element is 1
    for i in range(1, n + 1):
        a[i] = a[i - 1] + (-1 if a[i] == 0 else 1)
    # Check if any segment is beautiful (more ones than zeros)
    for i in range(1, m + 1):
        # a[r[i]] - a[l[i] - 1] gives the difference in ones and zeros in segment [l[i], r[i]]
        # If this difference is positive, the number of ones is greater than zeros
        if a[r[i]] - a[l[i] - 1] > 0:
            return True
    return False


while t > 0:
    global n, m
    n, m = map(int, rline().split())
    for i in range(1, m + 1):
        l[i], r[i] = map(int, rline().split())
    q = int(rline())
    for i in range(1, q + 1):
        x[i] = int(rline())
    low = 1
    high = q
    while low <= high:
        mid = (low + high) // 2
        if check(mid):
            high = mid - 1
        else:
            low = mid + 1
    print(-1 if low == q + 1 else low)
    t -= 1


# https://github.com/VaHiX/CodeForces/