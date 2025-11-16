# Problem: CF 1942 D - Learning to Paint
# https://codeforces.com/contest/1942/problem/D

"""
Algorithm: Dynamic Programming with Priority Queue (Heap)
Time Complexity: O(n^2 * k * log(n))
Space Complexity: O(n^2 + k)

This solution uses dynamic programming to compute the k largest possible beauty values
of paintings on a canvas. For each position, we maintain a list of the k largest
beauty values achievable up to that point. A min-heap is used to efficiently track
the k largest values.

The key idea is:
- dp[i] stores the k largest beauty values using only cells from 1 to i.
- For each new cell i, we compute the new beauty values by combining previous
  results with the cost of painting the interval ending at cell i.
- A heap is used to maintain potential candidates efficiently.

The matrix 'mat' stores the beauty values for intervals [i, j] where i <= j.
"""

import heapq
import sys

input = sys.stdin.readline


def solve():
    n, k = map(int, input().split())
    # Initialize the matrix to store beauty values of intervals
    mat = [[-1] * n for _ in range(n)]
    for i in range(n):
        a = list(map(int, input().split()))
        for j in range(i, n):
            mat[i][j] = a[j - i]

    # dp[i] will store the k largest beauty values using cells 1..i
    dp = [[] for _ in range(n + 1)]
    dp[0] = [0]  # Base case: 0 beauty when no cells are painted

    for i in range(1, n + 1):
        # Initialize heap with possible candidates for the current step
        h = [(-dp[j][0] - mat[j + 1][i - 1], j) for j in range(i - 1)]
        heapq.heapify(h)
        heapq.heappush(h, (-dp[i - 1][0], i - 1))  # Cost of extending previous interval
        heapq.heappush(h, (-mat[0][i - 1], -1))     # Cost of starting new interval

        ind = [0] * i  # Track indices for each dp[j] to generate next candidates
        while h and len(dp[i]) < k:
            v, j = heapq.heappop(h)
            v = -v  # Convert back from negative heap value
            dp[i].append(v)
            # If this candidate is not the last in the sequence,
            # and there are more candidates from dp[j], add them to heap
            if j < 0 or ind[j] + 1 >= len(dp[j]):
                continue
            ind[j] += 1
            if j != i - 1:
                # Continue with the next candidate from dp[j]
                heapq.heappush(h, (-dp[j][ind[j]] - mat[j + 1][i - 1], j))
            else:
                # Extend the same interval
                heapq.heappush(h, (-dp[i - 1][ind[j]], i - 1))

    print(*dp[-1])


t = int(input())

for _ in range(t):
    solve()


# https://github.com/VaHiX/CodeForces/