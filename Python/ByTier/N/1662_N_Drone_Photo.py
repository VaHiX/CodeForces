# Problem: CF 1662 N - Drone Photo
# https://codeforces.com/contest/1662/problem/N

"""
Code Purpose:
This code solves the problem of counting valid ways to select four contestants forming the vertices of an axis-aligned rectangle, 
such that the two poles (formed by contestants with the youngest and oldest ages among the four) do not cross. 

Algorithm:
- For each contestant, store their row and column index based on age.
- Iterate through all contestants in increasing order of age.
- For each contestant, count how many previously selected contestants are in the same row and column.
- The combinations of previous contestants in the same row/column represent valid pole configurations that avoid crossing.
- The total number of rectangles is calculated using combinatorics, then subtracted from valid configurations to get the result.

Time Complexity: O(n^2)
Space Complexity: O(n^2)

"""

import sys

input = sys.stdin.readline
n = int(input())
o1 = [0] * (n * n)
o2 = [0] * (n * n)
for i in range(n):
    curr = list(map(int, input().split()))
    for j in range(n):
        # Store the row and column index for each contestant based on their age
        o1[curr[j] - 1] = i
        o2[curr[j] - 1] = j

# Initialize counters for rows and columns
row_count = [0] * n
col_count = [0] * n

ct = 0  # Counter for valid pole arrangements
for u in range(n * n):
    i = o1[u]
    j = o2[u]
    # Add valid combinations from previous contestants in same row/column
    ct += row_count[i] * col_count[j]
    # Update counts after processing current contestant
    row_count[i] += 1
    col_count[j] += 1

# Total number of possible rectangles (axis-aligned)
n2 = (n * n - n) // 2
ct -= n2 * n2  # Subtract total rectangles, as these are all invalid crossings

# Print final result
print(n2 * n2 - ct)


# https://github.com/VaHiX/CodeForces/