# Problem: CF 889 A - Petya and Catacombs
# https://codeforces.com/contest/889/problem/A

"""
Algorithm: Greedy Approach with Set Tracking
Purpose: Determine the minimum number of rooms required to satisfy the logbook entries.
Approach:
- For each note in the logbook, we check if the room corresponding to that note was visited before.
- If it was, we can reuse the previously assigned room.
- If not, we must assign a new room.
- The key idea is to track the last time each room was visited using a set.
- The minimum number of rooms is computed by subtracting the count of unique entries from the total number of visits.

Time Complexity: O(n), where n is the number of entries in the logbook.
Space Complexity: O(n), for storing the set of visited room identifiers.
"""

import sys

readline = sys.stdin.readline

N = int(readline())
T = list(map(int, readline().split()))
ans = N + 1 - len(set(T))  # Compute minimum rooms using unique entries
print(ans)


# https://github.com/VaHiX/CodeForces/