# Problem: CF 1941 E - Rudolf and k Bridges
# https://codeforces.com/contest/1941/problem/E

"""
Algorithm: Dynamic Programming with Sliding Window
Time Complexity: O(n * m)
Space Complexity: O(n * m)

This solution solves the problem of building k bridges on consecutive rows
of a river grid such that the total cost of supports is minimized.

Key techniques:
1. For each row, compute the minimum cost to place supports ensuring
   maximum distance d between adjacent supports using a sliding window
   with a monotonic queue.
2. Then, use another sliding window to find the minimum sum of k consecutive
   row costs.

The algorithm uses a deque to maintain a monotonic queue for efficient
computation of minimum support costs per row, and a second sliding window
to choose the optimal k consecutive rows.
"""

import sys
from collections import deque


def I():
    return int(sys.stdin.readline().strip())


def IL():
    return list(map(int, sys.stdin.readline().strip().split()))


def S():
    return sys.stdin.readline().strip()


def solve():
    n, m, k, d = IL()
    grid = [IL() for _ in range(n)]
    cost_per_row = []

    for row in range(n):
        que = deque([1])  # Initialize deque with cost for first cell (0-indexed)
        left = 0
        grid[row][0] = 1  # Cost to place support at first column is 1
        for col in range(1, m):
            # Calculate cost for current cell based on minimum previous cost plus current depth
            cur_cost = que[0] + grid[row][col] + 1
            # Maintain monotonic property of deque
            while que and que[-1] > cur_cost:
                que.pop()
            que.append(cur_cost)
            grid[row][col] = cur_cost
            # Slide window if distance exceeds d
            if col - left - 1 >= d:
                if que and que[0] == grid[row][left]:
                    que.popleft()
                left += 1
        cost_per_row.append(grid[row][-1])

    ans = float("inf")
    l = cur = 0
    for r in range(n):
        cur += cost_per_row[r]
        if r - l + 1 >= k:
            ans = min(ans, cur)
            cur -= cost_per_row[l]
            l += 1
    print(ans)


for _ in range(I()):
    solve()


# https://github.com/VaHiX/CodeForces/