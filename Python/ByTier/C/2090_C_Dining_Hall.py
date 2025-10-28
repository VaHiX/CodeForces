# Problem: CF 2090 C - Dining Hall
# https://codeforces.com/contest/2090/problem/C

"""
C. Dining Hall

Purpose:
This code simulates guests entering a dining hall and choosing table cells based on their characteristics (0 or 1).
The hall is structured as an infinite grid with tables occupying 2x2 blocks of cells in a specific pattern.
Guests choose the nearest unoccupied table cell, applying different strategies based on whether they are type 0 or type 1.

Algorithm:
- Precompute table cell coordinates in a specific order.
- Maintain counters for next available cells (for both types of guests).
- Use greedy selection when placing guests.

Time Complexity:
O(n) where n is the total number of guests across all test cases. The process is linear with respect to the input size, due to precomputed structure and single pass processing.

Space Complexity:
O(n) for storing the result list of table cell coordinates.

Techniques:
- Greedy selection based on distance and ordering.
- Precompute table locations using modular arithmetic and counter logic.
"""

import sys

input = sys.stdin.readline
print = sys.stdout.write
t = int(input())
for _ in range(t):
    n = int(input())
    s = list(map(int, input().split()))[::-1]  # Reverse to pop from end
    rst = []
    m2 = 2   # Next candidate for 2x2 table (type 0 guest)
    m2_c = 0 # Count of cells assigned in current group for m2
    m3 = 3   # Next candidate for 3x3 table (type 1 guest)
    m3_c = 0 # Count of cells assigned in current group for m3
    while s:
        i = s.pop()
        if i == 0 or m2 < m3:  # Case when type 0 guest or m2 is closer than m3
            x = 1 + 3 * m2_c   # Compute x coordinate based on current group
            y = m2 - x         # Compute y coordinate
            rst.append((x, y)) # Append the chosen table cell
            m2_c += 1          # Increment counter for current group
            if m2 + 1 == 3 * m2_c:  # If all cells in this group used
                m2 += 3         # Move to next block of size 2x2
                m2_c = 0        # Reset counter
        else:
            # Type 1 guest or m3 is closer, handle differently
            if m3_c % 3 == 0:
                x = 1 + m3_c      # Compute x for first case in group
                y = m3 - x        # Compute y based on x and current limit
            elif m3_c % 3 == 1:
                x = 1 + m3_c      # Compute x for second case in group
                y = m3 - x - 2    # Compute appropriate y with offset
                if m3 == m3_c + 2:  # Special handling when at edge
                    y += 2
            elif m3_c % 3 == 2:
                x = m3_c          # Compute x for third case in group
                y = m3 - x        # Compute y
            rst.append((x, y))   # Append selected table cell
            m3_c += 1            # Increment counter for current group
            if m3 == m3_c + 1:   # If end of block reached
                m3 += 3          # Move to next block
                m3_c = 0         # Reset block counter
    for i in rst:
        print(f"{i[0]} {i[1]}\n")


# https://github.com/VaHiX/codeForces/