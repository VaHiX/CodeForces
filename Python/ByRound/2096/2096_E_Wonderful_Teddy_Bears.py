# Problem: CF 2096 E - Wonderful Teddy Bears
# https://codeforces.com/contest/2096/problem/E

"""
E. Wonderful Teddy Bears

Purpose:
This code solves the problem of reordering teddy bears to make a "beautiful" arrangement,
where all black bears (B) are to the left of all pink bears (P). The allowed operation is
to select three consecutive positions and sort them so B's are to the left of P's.

Algorithm:
- The approach is based on tracking how many B's have been placed correctly.
- For each B encountered in the string, we determine if it is already in a correct position,
  or needs to be moved via an operation.
- We maintain two counters: 'ev' for even-indexed B placements (used when placing B's),
  and 'od' for odd-indexed B placements (used to track alternative placements).
- For each B, we calculate how many operations are needed based on the current index and
  expected placement.

Time Complexity: O(n), where n is the length of the string s.
Space Complexity: O(1), constant space usage.

"""

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n = int(input())
    s = input().strip()
    num = 0
    sol = 0
    ev = 0  # Tracks even position for B placement
    od = 1  # Tracks odd position for B placement
    cnt = s.count("B")  # Total number of black bears
    
    for i in range(n):
        if s[i] == "B":
            # Determine whether to use even or odd tracking strategy
            if (ev < cnt and (i - ev) % 2 == 0 and i >= ev) or od >= cnt or i < od:
                # Use even strategy to assign this B
                sol += (i - ev + 1) // 2
                ev += 2
            else:
                # Use odd strategy to assign this B
                sol += (i - od + 1) // 2
                od += 2
    print(sol)


# https://github.com/VaHiX/codeForces/