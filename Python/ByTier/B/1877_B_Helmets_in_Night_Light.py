# Problem: CF 1877 B - Helmets in Night Light
# https://codeforces.com/contest/1877/problem/B

"""
Algorithm: Greedy approach with sorting
- Sort residents by the cost of sharing (b[i]) in ascending order.
- Initially, we must notify at least one resident directly (cost p).
- For each resident (in sorted order of sharing cost), we use their ability to share to other residents.
- To minimize cost, prioritize using residents with lower sharing costs.
- If sharing cost is greater than or equal to direct notification cost, skip that resident.
- Continue until all residents are notified.
Time Complexity: O(n log n) due to sorting and linear pass
Space Complexity: O(n) for storing indices and auxiliary arrays
"""

import sys

input = sys.stdin.readline


def readList():
    return list(map(int, input().split()))


def readInt():
    return int(input())


def readInts():
    return map(int, input().split())


def readStr():
    return input().strip()


def solve():
    n, p = readInts()
    a, b = readList(), readList()
    # Sort indices based on sharing cost b[i] in ascending order
    idx = sorted([i for i in range(n)], key=lambda x: b[x])
    # Remove residents whose sharing cost is >= direct notification cost
    while idx and b[idx[-1]] >= p:
        idx.pop()
    # Start with one direct notification
    cost, curr = p, n - 1
    # Iterate through sorted indices and optimally distribute notifications
    for i in idx:
        if not curr:
            break
        # Determine how many people this resident can notify
        cnt = min(curr, a[i])
        # Add cost for sharing
        cost += cnt * b[i]
        # Update remaining residents to notify
        curr -= cnt
    # If there are still residents left, notify them directly
    return cost + curr * p


for _ in range(int(input())):
    print(solve())


# https://github.com/VaHiX/CodeForces/