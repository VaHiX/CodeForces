# Problem: CF 2104 B - Move to the End
# https://codeforces.com/contest/2104/problem/B

"""
B. Move to the End
Algorithms/Techniques: Prefix max array, reverse iteration, greedy selection

Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

For each k from 1 to n:
- We want to maximize the sum of last k elements after moving one element to the end.
- The key insight is that we should move the element which, when moved to the end,
  maximizes the contribution of the last k elements.
- To compute efficiently, we precompute prefix maximums to determine optimal moves.
"""

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    b = [0]
    for j in range(n):
        b.append(max(b[-1], a[j]))  # Precompute prefix max to know maximum element seen so far
    out = []
    cur = 0
    for j in range(n - 1, -1, -1):
        cur += a[j]
        # For current position, calculate sum of last k elements with optimal move
        out.append(cur + max(0, b[j] - a[j]))
    print(*out)


# https://github.com/VaHiX/codeForces/