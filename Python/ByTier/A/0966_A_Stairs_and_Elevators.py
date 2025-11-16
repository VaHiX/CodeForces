# Problem: CF 966 A - Stairs and Elevators
# https://codeforces.com/contest/966/problem/A

"""
Algorithm: Shortest Path on Grid with Stairs and Elevators
Time Complexity: O(q * log(m)) where q is the number of queries and m is the number of sections per floor
Space Complexity: O(c_l + c_e) where c_l and c_e are the number of stairs and elevators

Approach:
- For each query, we compute the minimum time to travel from (x1, y1) to (x2, y2)
- If we're on the same floor, we only need to move horizontally: cost = |y1 - y2|
- Otherwise, we can use either stairs or elevators:
  - Stairs: go to the nearest stair, use it to go up/down, then move horizontally
  - Elevators: go to the nearest elevator, take it to the target floor, then move horizontally
- Use binary search to find the nearest stair/elevator to a given section to optimize search
"""

import sys

input = lambda: sys.stdin.readline()[:-1]
ni = lambda: int(input())
na = lambda: list(map(int, input().split()))
yes = lambda: print("yes")
Yes = lambda: print("Yes")
YES = lambda: print("YES")
no = lambda: print("no")
No = lambda: print("No")
NO = lambda: print("NO")
n, m, cl, ce, v = na()
l = na()
e = na()
q = ni()
from bisect import bisect_left as bl

for _ in range(q):
    x1, y1, x2, y2 = na()
    ans = 10**18
    if x1 == x2:
        print(abs(y1 - y2))
    else:
        # Find the nearest stair to y1
        Y = bl(l, y1)
        if Y < len(l):
            # If there's a stair at or after y1, use it
            ans = min(ans, abs(y1 - l[Y]) + abs(y2 - l[Y]) + abs(x1 - x2))
        if Y > 0:
            # If there's a stair before y1, use it
            ans = min(ans, abs(y1 - l[Y - 1]) + abs(y2 - l[Y - 1]) + abs(x1 - x2))
        
        # Find the nearest elevator to y1
        Y = bl(e, y1)
        if Y < len(e):
            # If there's an elevator at or after y1, use it
            ans = min(
                ans, abs(y1 - e[Y]) + abs(y2 - e[Y]) + (abs(x1 - x2) - 1) // v + 1
            )
        if Y > 0:
            # If there's an elevator before y1, use it
            ans = min(
                ans,
                abs(y1 - e[Y - 1]) + abs(y2 - e[Y - 1]) + (abs(x1 - x2) - 1) // v + 1,
            )
        print(ans)


# https://github.com/VaHiX/CodeForces/