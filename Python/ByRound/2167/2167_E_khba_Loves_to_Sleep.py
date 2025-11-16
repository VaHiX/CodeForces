# Problem: CF 2167 E - khba Loves to Sleep!
# https://codeforces.com/contest/2167/problem/E

"""
Algorithm: Binary Search + Greedy Placement
Approach:
- We want to place k teleports to maximize the minimum time for any friend to reach the nearest teleport.
- This is a classic "maximize the minimum" optimization problem which can be solved using binary search on the answer.
- For a given minimum distance m, we compute how many teleport positions we can place within [0, x] such that every friend's nearest teleport is at least m distance away.
- Once we determine the maximum possible m (minimum distance), we greedily place the k teleports in the intervals where maximum spacing is possible.

Time Complexity: O(n * log(x)) per test case due to sorting and binary search.
Space Complexity: O(n) for storing sorted positions and result array.
"""

import sys

input = lambda: sys.stdin.readline().rstrip("\r\n")
sint = lambda: int(input())
mint = lambda: map(int, input().split())
aint = lambda: list(map(int, input().split()))


T = sint()
for _ in range(T):
    n, k, x = mint()
    
    a = aint()
    a.sort()  # Sort friends' positions for easier processing
    
    # Binary search on the best minimum distance
    L = 0
    R = x + 1  # Upper bound for possible minimum distance
    while R - L > 1:
        m = (L + R) // 2  # Midpoint of current search range
        tot = max(0, a[0] - m + 1) + max(0, x - a[-1] - m + 1)  # Count of spots in first and last segments
        for i in range(n - 1):
            # For consecutive friends, compute number of slots in the gap between them
            tot += max(0, (a[i + 1] - a[i]) - 2 * m + 1)
        if tot >= k:
            L = m  # Try to increase the minimum distance
        else:
            R = m  # Reduce the minimum distance
    
    # Once we know the best minimum distance (L), we place k teleports greedily
    if L == 0:
        # If min distance is 0, we can place all k teleports at any k positions
        ans = [i for i in range(k)]
    else:
        ans = []
        # Place teleports where needed before the first friend
        for i in range(a[0] - L + 1):
            ans.append(i)
        # Place teleports where needed after the last friend
        for i in range(a[-1] + L, x + 1):
            ans.append(i)
        # Place teleports in between friends
        for i in range(n - 1):
            for j in range(a[i] + L, a[i + 1] - L + 1):
                ans.append(j)
    
    print(*ans[:k])  # Output only the first k positions


# https://github.com/VaHiX/CodeForces/