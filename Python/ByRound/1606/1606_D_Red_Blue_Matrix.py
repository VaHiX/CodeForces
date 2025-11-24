# Problem: CF 1606 D - Red-Blue Matrix
# https://codeforces.com/contest/1606/problem/D

"""
Algorithm: Red-Blue Matrix
Approach: 
1. Sort rows by first column value
2. Use dynamic programming to find valid cuts
3. Check constraints for perfect coloring

Time Complexity: O(n * m * log(n)) where n is rows, m is columns
Space Complexity: O(n * m) for storing matrix and auxiliary arrays

The algorithm attempts to find a valid coloring and cut such that:
- All red cells in left matrix > all blue cells in left matrix  
- All blue cells in right matrix > all red cells in right matrix
"""

import sys

for _ in range(int(sys.stdin.readline())):
    n, m = [int(i) for i in sys.stdin.readline().split()]
    a = [[int(i) for i in sys.stdin.readline().split()] for i in range(n)]
    for i in range(n):
        a[i].append(i)  # Append original row index
    a.sort(key=lambda x: x[0])  # Sort by first column value
    a = list(zip(*a))  # Transpose to get columns as rows for easier processing
    
    d = [0] * n  # Dynamic programming array to track valid splits
    d[0] = 1  # First element is always valid
    lastd = []
    ma, mi = [0] * n, [10000000] * (n + 1)  # max and min arrays for tracking
    
    # Process columns from left to right
    for idx, x in enumerate(a[:-1]):  # Exclude last column (for cut position)
        ma[0] = max(ma[0], x[0])  # Update maximum for first row
        for i in range(1, n):
            ma[i] = max(ma[i], ma[i - 1], x[i])  # Update max array
        lastd = d[:]  # Save current state
        for i in range(n - 1, 0, -1):  # Process backwards
            mi[i] = min(mi[i], mi[i + 1], x[i])  # Update min array
            if mi[i] <= ma[i - 1]:  # Check perfect condition
                d[i] = 1
        if all(d):  # If all positions are valid
            break
    
    d = lastd  # Restore last valid state
    ma, mi = [-10000000] * n, [0] * (n + 1)  # Reset arrays for reverse pass
    
    # Process columns from right to left (reverse pass)
    for x in a[idx:-1][::-1]:  # Process remaining columns in reverse
        ma[0] = max(ma[0], -x[0])  # Negative for reverse logic
        for i in range(1, n):
            ma[i] = max(ma[i], ma[i - 1], -x[i])
        for i in range(n - 1, 0, -1):
            mi[i] = min(mi[i], mi[i + 1], -x[i])
            if mi[i] <= ma[i - 1]:
                d[i] = 1
        if all(d):  # If still all valid
            print("NO")  # No perfect coloring found
            break
    else:
        # Construct result
        i = d.index(0)  # Find first invalid position
        r = ["R"] * n  # Initialize with all red
        for j in a[-1][:i]:  # Mark first i positions as blue in original order
            r[j] = "B"
        print("YES\n%s %d" % ("".join(r), idx))  # Print result


# https://github.com/VaHiX/CodeForces/