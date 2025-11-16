# Problem: CF 1850 G - The Morning Star
# https://codeforces.com/contest/1850/problem/G

"""
Compass Direction Pairing Problem

Algorithm:
- For each point, we compute 4 values based on coordinates:
  - x
  - y
  - x + y (diagonal direction)
  - x - y (anti-diagonal direction)
- These values represent directional combinations.
- For each of the four computed arrays, we sort and count duplicates:
  - If two points have the same value in one of these arrays,
    they form valid compass directions (since the compass points
    in one of the eight defined directions, based on coordinate differences).
- The total valid pairs are doubled because order matters (compass vs star).

Time Complexity: O(n log n) per test case due to sorting,
Space Complexity: O(n) for storing coordinate values.
"""

import sys

input = sys.stdin.readline

for _ in range(int(input())):
    n = int(input())
    # Initialize array for storing 4 types of coordinate combinations
    a = [n * [0], n * [0], n * [0], n * [0]]
    for i in range(n):
        x = [int(j) for j in input().rstrip().split()]
        a[0][i] = x[0]          # x-coordinate
        a[1][i] = x[1]          # y-coordinate
        a[2][i] = x[0] + x[1]   # x + y (diagonal)
        a[3][i] = x[0] - x[1]   # x - y (anti-diagonal)

    ans = 0
    # For each of the four coordinate types
    for i in range(4):
        a[i].sort()  # Sort to group identical values
        p = 0        # Previous value
        cnt = 0      # Count of current value
        for j in a[i]:
            if j == p:
                ans += cnt  # Add number of previous same values to result
                cnt += 1    # Increment current count
            else:
                cnt = 1     # Reset count
            p = j           # Update previous value
    
    ans *= 2  # Each valid pair is counted twice (once for each order)
    print(ans)


# https://github.com/VaHiX/CodeForces/