# Problem: CF 2059 C - Customer Service
# https://codeforces.com/contest/2059/problem/C

"""
C. Customer Service

Algorithm:
The problem involves choosing an order to service queues such that the MEX (minimum excluded value) of final queue sizes is maximized.
This can be solved by using a greedy approach combined with dynamic programming ideas.

Key insight:
- We want to maximize MEX of the remaining queue sizes.
- The MEX of a set of numbers is the smallest non-negative integer not present in the set.
- For each step (time moment), we process queues in a way that attempts to leave as many small values (0,1,2,...) as possible.

Approach:
1. For each row in matrix 'a', reverse the row to simulate processing time backwards.
2. Sort rows of matrix based on their reversed representation.
3. Traverse from bottom to top and find how many consecutive positions (starting from 0) can be filled with value 1.
4. The result is the count of such positions + 1.

Time Complexity: O(n^2 log n) - due to sorting the rows.
Space Complexity: O(n^2) - to store the input matrix and process reverse sort.

"""

import sys

input = sys.stdin.readline
t = int(input())
for _ in range(t):
    n = int(input())
    a = [list(map(int, input().split())) for _ in range(n)]
    # Reverse each row to simulate backward time processing
    for i in range(n):
        a[i].reverse()
    # Sort the rows lexicographically (after reverse)
    a.sort()
    # Traverse from bottom-right to top-left to count how many 1s we can keep
    i = n - 2  # Start one row before last
    j = 0      # Count of positions that can be made 0
    while i >= 0 and j < n:
        if a[i][j] == 1:
            j += 1  # Increment when we see a 1; means this position is usable
        i -= 1
    print(j + 1)  # Return the MEX value which is one more than number of zeros we can place


# https://github.com/VaHiX/codeForces/