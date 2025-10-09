# Problem: CF 2024 D - Skipping
# https://codeforces.com/contest/2024/problem/D

"""
Problem: Maximum Points in a Modified Olympiad

Algorithms/Techniques:
- Fenwick Tree (Binary Indexed Tree)
- Dynamic Programming with optimization using BIT
- Greedy approach with backward processing

Time Complexity: O(n log n) per test case
Space Complexity: O(n) for the Fenwick tree and auxiliary arrays

This code solves a dynamic programming problem where Prokhor must choose which problems to submit 
or skip in order to maximize his score, given specific rules about how the next problem is selected.

The core idea is to process problems from right to left and use a Fenwick Tree to efficiently query 
and update minimum cost (in terms of points lost) for selecting each problem.
"""

from sys import stdin

input = lambda: stdin.buffer.readline().decode().strip()
from math import inf


class Fenwick:
    def __init__(self, n, func=min):
        self.n = n + 1
        self.tree = [inf] * self.n
        self.func = func

    def query(self, i):
        x = inf
        while i > 0:
            x = self.func(self.tree[i], x)
            i -= i & -i
        return x

    def update(self, i, x):
        while i < self.n:
            self.tree[i] = self.func(x, self.tree[i])
            i += i & -i


for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    pre = ans = 0
    cost = Fenwick(n)
    cost.update(n, 0)
    for i in range(n):
        pre += a[i]
        c = cost.query(n - i)  # Query the minimum cost to reach this index
        cost.update(n - b[i] + 1, c + a[i])  # Update with new cost
        ans = max(ans, pre - c)  # Calculate maximum points achievable so far
    print(ans)


# https://github.com/VaHiX/codeForces/