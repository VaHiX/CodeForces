# Problem: CF 2014 D - Robert Hood and Mrs Hood
# https://codeforces.com/contest/2014/problem/D

"""
D. Robert Hood and Mrs Hood

Purpose:
This code solves a problem where Robin needs to select start days for his brother's and mother's visits such that:
- Both visits last for 'd' consecutive days,
- Visits must fit within days 1 to n,
- Brother's visit overlaps with maximum number of jobs,
- Mother's visit overlaps with minimum number of jobs.

Algorithm:
- Use a difference array technique to efficiently compute job overlaps for each possible start day.
- Difference array is used to mark the beginning and end of job intervals.
- Then compute prefix sum to get actual overlap counts for each start day.
- Finally, find the best start day for brother (max overlap) and mother (min overlap).

Time Complexity: O(n + k) per test case
Space Complexity: O(n + d) for the difference array

Input Format:
t - number of test cases
n, d, k - days, visit duration, number of jobs
k lines of l, r - job start and end days

Output Format:
Best start day for brother and mother respectively.
"""

import sys

input = lambda: sys.stdin.readline().strip()
t = int(input())
for _ in range(t):
    n, d, k = map(int, input().split())
    ps = [0] * (n + d + 10)  # Difference array to track job overlaps
    for i in range(k):
        l, r = map(int, input().split())
        r += d  # Extend the range by 'd' days since visit spans 'd' days
        ps[l] += 1    # Mark start of interval
        ps[r] -= 1    # Mark end of interval (exclusive)
    
    # Compute prefix sum to get actual overlaps for each day
    for i in range(1, len(ps)):
        ps[i] += ps[i - 1]
    
    # Extract only valid start days (from day d to n-d+1), these are the possible visit start days
    ps = ps[d : n + 1]
    
    # Find index of maximum and minimum overlap counts in the range (1-indexed)
    print(
        max(range(1, n - d + 2), key=lambda i: ps[i - 1]),  # Brother's best start day (max overlap)
        min(range(1, n - d + 2), key=lambda i: ps[i - 1]),  # Mother's best start day (min overlap)
    )


# https://github.com/VaHiX/codeForces/