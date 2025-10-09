# Problem: CF 2110 C - Racing
# https://codeforces.com/contest/2110/problem/C

"""
C. Racing

Purpose:
This code solves a problem where a drone must navigate through a sequence of obstacles,
each with a height constraint [l_i, r_i]. The drone's movement between obstacles is defined 
by a difference array `d`, where each element can be 0 or 1 (or -1 for unknown). 
The task is to assign values to the -1 positions such that the cumulative height stays 
within all obstacle constraints.

Algorithms/Techniques:
- Two-pointer sliding window technique with stack-based tracking of -1 elements
- Greedy assignment of 0s and 1s while maintaining bounds

Time Complexity: O(n) per test case, where n is the number of obstacles.
Space Complexity: O(n) for storing the difference array and auxiliary stack.

Input:
Each test case consists of:
    - n (number of obstacles)
    - Array d of size n with values in {-1, 0, 1}
    - For each obstacle i, two integers l_i and r_i defining valid height range

Output:
For each case, output the completed array d or -1 if impossible.
"""

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    s = []  # Stack to store indices of -1 elements
    u, v, f = 0, 0, 1  # u: count of 1s, v: current height, f: flag for feasibility
    
    for j in range(n):
        l, r = map(int, input().split())
        if a[j] == -1:
            s.append(j)  # Track index of unknown value
            v += 1       # Assume we climb by 1 to reach max height at that point
        elif a[j] == 1:
            u += 1       # Count of 1s increases 
            v += 1       # Height also climbs by 1
            
        # If current height exceeds upper bound, we must reduce it by changing some 1s to 0s
        while v > r and s:
            a[s.pop()] = 0   # Change 1s in stack to 0 (climb down)
            v -= 1           # Reduce height accordingly
            
        # If count of 1s is below lower bound, we must change 0s to 1s
        while u < l and s:
            a[s.pop()] = 1   # Change 0 to 1 to increase count of 1s
            u += 1           # Increase number of climbs
            
        # Check if current height or number of climbs violates constraints
        if v < u or v > r or u < l:
            f = 0    # Set flag to indicate failure
            
    # After processing, reset remaining -1s to 0 to ensure final heights are valid
    for j in range(n):
        if a[j] == -1:
            a[j] = 0
            
    # Print result or -1 if impossible
    if f:
        print(*a)
    else:
        print(-1)


# https://github.com/VaHiX/codeForces/