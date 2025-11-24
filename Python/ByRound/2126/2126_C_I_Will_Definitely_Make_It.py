# Problem: CF 2126 C - I Will Definitely Make It
# https://codeforces.com/contest/2126/problem/C

"""
C. I Will Definitely Make It

Algorithm/Approach:
- The problem involves finding whether we can reach a tower with maximum height before water level exceeds tower height.
- Key insight: Start from the k-th tower, sort all towers by height to consider them in increasing order.
- For each tower in the sorted list, if it's higher than current water level (s), calculate time needed to teleport.
- If accumulated time exceeds current water level, return "NO".
- If we successfully traverse all reachable towers without exceeding water level, return "YES".

Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing the list of heights

"""
import sys

I = sys.stdin.readline
for _ in range(int(I())):
    n, k = map(int, I().split())
    l = [*map(int, I().split())]
    s = l[k - 1]  # Initial water level is the height of the starting tower
    l.sort()  # Sort heights to process in ascending order
    w = 0     # Accumulated time spent teleporting
    f = 1     # Flag to determine if path exists
    for e in l:
        if e > s:  # Only consider towers higher than current water level
            w += e - s  # Add teleportation time
            if w > s:   # If accumulated time exceeds water level, impossible to proceed
                print("NO")
                f = 0
                break
            s = e  # Move to new tower
    if f:
        print("YES")


# https://github.com/VaHiX/codeForces/