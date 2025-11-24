# Problem: CF 2013 D - Minimize the Difference
# https://codeforces.com/contest/2013/problem/D

"""
D. Minimize the Difference

Purpose:
Given an array of integers, we can perform operations where we decrease an element by 1 and increase the next element by 1.
The goal is to minimize the difference between the maximum and minimum values in the array after any number of such operations.

Algorithm:
This problem uses a prefix sum approach combined with binary search logic. We compute prefix sums from both ends and track
the minimum possible floor average (lo) and maximum possible ceiling average (hi) that can be achieved by redistributing elements.
The idea is to iterate through all positions, maintaining running totals from left and right, and for each position,
compute the average of the prefix (rounded down for lo, rounded up for hi), then find the difference (hi - lo).

Time Complexity: O(n) per test case
Space Complexity: O(1)

"""
import sys

input = sys.stdin.readline
t = int(input())
o = []
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    lo = 10**15   # Initialize to a large number for tracking minimum average
    hi = 0        # Initialize to 0 for tracking maximum average
    tl = tr = 0   # tl: total sum from left, tr: total sum from right
    for i in range(n):
        tl += a[i]                        # Accumulate prefix sum from left
        tr += a[~i]                       # Accumulate suffix sum from right (using bitwise negation)
        lo = min(lo, tl // (i + 1))       # Minimum possible floor average so far
        hi = max(hi, (tr + i) // (i + 1)) # Maximum possible ceiling average so far
    o.append(hi - lo)
print("\n".join(map(str, o)))


# https://github.com/VaHiX/codeForces/