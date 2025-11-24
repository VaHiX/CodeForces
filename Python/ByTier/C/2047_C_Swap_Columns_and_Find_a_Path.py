# Problem: CF 2047 C - Swap Columns and Find a Path
# https://codeforces.com/contest/2047/problem/C

# ==============================================================================
# Problem: C. Swap Columns and Find a Path
# Purpose: Maximize the sum of a path from (1,1) to (2,n) by swapping columns optimally.
# Algorithm: For each column, we compute max(a[i][j], b[i][j]) and min(a[i][j], b[i][j]).
#            The maximum path sum is sum(maxes) + max(mins), where:
#            - maxes[i] = max(a[i][j], b[i][j]) for column j
#            - mins[i] = min(a[i][j], b[i][j]) for column j
# Time Complexity: O(n) per test case
# Space Complexity: O(n) for storing maxes and mins arrays
# ==============================================================================

import sys

input = sys.stdin.readline
t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    
    # Compute maximum value for each column
    maxes = [max(i, j) for i, j in zip(a, b)]  # O(n)
    
    # Compute minimum value for each column
    mins = [min(i, j) for i, j in zip(a, b)]  # O(n)
    
    # The maximum path sum is the sum of all max values plus the maximum of all min values
    print(sum(maxes) + max(mins))  # O(n)


# https://github.com/VaHiX/codeForces/