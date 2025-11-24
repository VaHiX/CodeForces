# Problem: CF 1662 L - Il Derby della Madonnina
# https://codeforces.com/contest/1662/problem/L

"""
L. Il Derby della Madonnina
Time Complexity: O(n log n)
Space Complexity: O(n)

Approach:
This problem can be solved using a greedy algorithm combined with the concept of Longest Increasing Subsequence (LIS). 
The key insight is to transform each kick into an interval [x, y], where x represents the earliest time we can reach position a_i
and y is the latest time we can reach that position. Then, we find the longest sequence of such intervals that don't overlap,
which corresponds to the maximum number of kicks we can monitor.

For each kick at time t_i and position a_i:
- Calculate B = t_i * v (maximum distance we can travel in time t_i)
- x = B - a_i (earliest position we can be at time t_i)
- y = B + a_i (latest position we can be at time t_i)

We then filter out invalid intervals (where either x < 0 or y < 0) and sort the remaining intervals.
Using binary search (bisect_right), we maintain an array representing the smallest ending position of all possible increasing subsequences,
which is equivalent to solving LIS with a twist.

The result is the length of this array, which equals the maximum number of non-overlapping intervals (kicks).
"""

import bisect
import sys

input = sys.stdin.buffer.readline
read = sys.stdin.buffer.read
N, V = map(int, input().split())
Ts = list(map(int, input().split()))
As = list(map(int, input().split()))
points = []
for T, A in zip(Ts, As):
    B = T * V  # Maximum distance reachable in time T at speed V
    x = B - A  # Earliest position that can be reached by time T
    y = B + A  # Latest position that can be reached by time T
    if x < 0 or y < 0:  # Ignore impossible intervals
        continue
    points.append((x, y))
points.sort()  # Sort intervals by starting point

lis = []  # Maintain list of smallest ending positions for increasing subsequences
for _, w in points:
    index = bisect.bisect_right(lis, w)  # Find insertion point to maintain sorted order
    if index < len(lis):
        lis[index] = w  # Replace existing value with smaller one
    else:
        lis.append(w)  # Append new element to extend subsequence
print(len(lis))  # Length of LIS corresponds to maximum number of kicks


# https://github.com/VaHiX/codeForces/