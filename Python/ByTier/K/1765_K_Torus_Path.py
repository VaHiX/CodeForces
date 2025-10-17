# Problem: CF 1765 K - Torus Path
# https://codeforces.com/contest/1765/problem/K

"""
K. Torus Path

Problem Description:
Given an n x n grid with non-negative integers, we need to find the maximum sum path from (1,1) to (n,n)
with special movement rules:
- Can only move right or down
- Moving right from last column teleports to first column in same row
- Moving down from last row teleports to first row in same column
- Cannot visit the same cell twice (start is counted as visited)

Algorithm:
1. Calculate total sum of all elements in grid
2. Identify the minimum element on the main diagonal (from top-right to bottom-left)
3. Subtract this minimum from the total sum
4. This works because we can always avoid one element on the diagonal path,
   and choosing the smallest avoids minimizing our score

Time Complexity: O(n^2) - We iterate through all elements once
Space Complexity: O(1) - Only using constant extra space
"""

from sys import stdin

input = stdin.buffer.readline
n = int(input())
mi = 10**9  # Initialize minimum to a large value
su = 0      # Initialize sum of all elements

for i in range(n):
    l = [int(x) for x in input().split()]  # Read and parse the row
    su += sum(l)                           # Add all elements in current row to total sum
    
    # Check if the element on anti-diagonal (top-right to bottom-left) is smaller than current minimum
    if l[n - i - 1] < mi:
        mi = l[n - i - 1]

# Subtract the smallest element on the diagonal from total sum
print(su - mi)


# https://github.com/VaHiX/codeForces/