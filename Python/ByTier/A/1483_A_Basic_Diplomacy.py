# Problem: CF 1483 A - Basic Diplomacy
# https://codeforces.com/contest/1483/problem/A

"""
Algorithm: Greedy Selection
Approach:
1. For each day, if only one friend is available, assign that friend.
2. For days with multiple friends, choose the friend who has been selected the least so far, 
   prioritizing the first friend if both have the same count.
3. After assigning all days, verify that no friend is chosen more than ceil(m/2) times.

Time Complexity: O(m * n) in worst case, but generally much better due to greedy nature
Space Complexity: O(m + n) for storing answers and friend counts

Techniques:
- Greedy algorithm
- Counting and tracking of selections
- Ceiling function for upper bound calculation
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

for _ in range(ni()):
    n, m = na()
    a = [0] * n  # Count of selections for each friend
    ans = [-1] * m  # Result array for each day's selection
    que = [na() for i in range(m)]  # Available friends for each day
    
    # First pass: handle days with only one available friend
    for i in range(m):
        q = que[i]
        if q[0] == 1:  # Only one friend available
            ans[i] = q[1]
            a[q[1] - 1] += 1  # Increment count for that friend (0-indexed)

    # Second pass: handle days with multiple friends
    for i in range(m):
        q = que[i]
        if q[0] > 1:  # Multiple friends available
            x, y = q[1], q[2]  # Take first two friends
            # Assign the friend with fewer selections so far
            if a[x - 1] < (m + 1) // 2:  # Check if x is under limit
                a[x - 1] += 1
                ans[i] = x
            else:  # Else assign y
                a[y - 1] += 1
                ans[i] = y

    # Validation: check if any friend exceeds allowed selection count
    f = 1
    for i in range(n):
        if a[i] > (m + 1) // 2:  # If count exceeds ceil(m/2)
            f = 0
            break
    
    if f:
        YES()
        print(*ans)
    else:
        NO()


# https://github.com/VaHiX/CodeForces/