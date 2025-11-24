# Problem: CF 2004 B - Game with Doors
# https://codeforces.com/contest/2004/problem/B

"""
B. Game with Doors
Algorithm: Interval overlap detection and minimal door locking calculation
Time Complexity: O(1) per test case - constant time operations
Space Complexity: O(1) - only using a fixed number of variables

The problem involves determining the minimum number of doors to lock between two intervals 
so that no path exists between any room in Alice's interval [l, r] and any room in Bob's interval [L, R].

Key insight:
- Doors are between consecutive rooms (i and i+1).
- To prevent Alice and Bob from meeting, we must block all potential paths.
- The minimum number of doors to lock equals the size of the overlapping region
  between the intervals [l,r] and [L,R], but adjusted for door positions.

Approach:
1. First check if intervals do not overlap at all → return 1 (lock one door).
2. Otherwise, find the overlap interval.
3. Calculate how many doors are in that overlap.
4. Adjust for edge cases where segments touch but don't fully overlap.
"""

import sys

input = sys.stdin.readline
for i in range(int(input())):
    l, r = map(int, input().split())
    a, b = map(int, input().split())
    if r < a or b < l:
        print(1)
    else:
        print(min(r, b) + int(r != b) - max(l, a) + int(a != l))


# https://github.com/VaHiX/codeForces/