# Problem: CF 1884 C - Medium Design
# https://codeforces.com/contest/1884/problem/C

"""
Algorithm: Sweep Line + Heap + Two Pointers
Time Complexity: O(n log n)
Space Complexity: O(n)

This problem involves selecting a subset of segments such that the difference 
between the maximum and minimum values in the resulting array is maximized. 

We use a sweep line approach:
- Process segments in order of their starting positions.
- Use a min-heap to keep track of ending positions of active segments.
- Use two counters (fe and be) to track how many segments start before current 
  position and end at or after current position.
- For each segment, update the active count and calculate the maximum difference 
  between active segments and the minimum of front and back counters.
"""

import os.path
import sys
from bisect import *
from collections import *
from heapq import *
from math import *
from random import randint

rrr = randint(8888, 88888)
if os.path.exists("input.txt"):
    sys.stdin = open("input.txt", "r")
    sys.stdout = open("output.txt", "w")
    print(rrr)


def sol():
    n, m = tuple(map(int, input().split()))
    nums = []
    for i in range(n):
        nums.append(tuple(map(int, input().split())))
    nums.sort()  # Sort segments by starting position
    ene = []  # Store ending positions of segments that start at 1
    i = 0
    while i < n and nums[i][0] == 1:
        ene.append(nums[i][1])
        i += 1
    ene.reverse()  # Reverse to process from largest to smallest
    fe = len(ene)  # Count of segments starting at 1
    be = 0  # Count of segments ending at m
    ovr = []  # Min-heap to store ending positions of active segments
    heapify(ovr)  # Initialize heap
    ct = 0  # Number of active segments
    ans = 0  # Maximum cost
    for i, j in nums:
        # Remove segments from heap whose end position < current start position
        while ovr and ovr[0] < i:
            heappop(ovr)
            ct -= 1
        # Remove segments from ene whose end position < current start position
        while ene and ene[-1] < i:
            ene.pop()
            fe -= 1
        # If segment ends at m, increment back counter
        if j == m:
            be += 1
        ct += 1  # Add current segment to active count
        heappush(ovr, j)  # Add segment's end position to heap
        # Update answer with max of (current active count - min of front/back counters)
        ans = max(ans, ct - min(fe, be))
    print(ans)


for _ in range(int(input())):
    sol()


# https://github.com/VaHiX/CodeForces/