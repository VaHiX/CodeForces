# Problem: CF 1842 E - Tenzing and Triangle
# https://codeforces.com/contest/1842/problem/E

"""
Code Purpose:
This code solves the problem of erasing all points on a 2D plane using two operations:
1. Draw a triangle defined by lines x=a, y=b, and x+y=k, with cost l*A where l is the side length.
2. Erase a specific point with cost c_i.

The approach uses a segment tree with dynamic updates to efficiently compute the maximum profit achievable by using triangles.
It employs dynamic programming where for each row (defined by k-y), it processes points and maintains the maximum value of using triangles.

Algorithms/Techniques:
- Dynamic Programming
- Segment Tree (with range updates and queries)
- Coordinate compression

Time Complexity:
- O(n * log k) where n is the number of points and k is the line coefficient
- The segment tree operations (update/query) are O(log k) each
- The loop over k rows contributes O(k) to the time complexity

Space Complexity:
- O(k + n) for the segment tree and storing points
"""
import os
import sys

if os.path.exists("in.txt"):
    file = open("in.txt")
    input = file.readline
else:
    input = sys.stdin.readline
from collections import defaultdict

readi = lambda: int(input())
readis = lambda: list(map(int, input().split()))
reads = lambda: input().rstrip()
readss = lambda: input().split()


class SEGMENTTREE_ADD_MAX:
    @staticmethod
    def max(a, b):
        return a if a > b else b

    def __init__(self, n=10**9, q=10**5):
        self.N = 1 << (n + 2).bit_length()
        self.A = defaultdict(int) if n > q * n.bit_length() else [0] * (self.N * 2)

    def update(self, l, r, x):
        A, N = self.A, self.N
        if l <= 0:
            r += N + 1
            while r > 1:
                if r & 1:
                    A[r ^ 1] += x
                tmp = SEGMENTTREE_ADD_MAX.max(A[r], A[r ^ 1])
                A[r] -= tmp
                A[r ^ 1] -= tmp
                A[r >> 1] += tmp
                r >>= 1
        elif r >= N - 1:
            l += N - 1
            while l > 1:
                if ~l & 1:
                    A[l ^ 1] += x
                tmp = SEGMENTTREE_ADD_MAX.max(A[l], A[l ^ 1])
                A[l] -= tmp
                A[l ^ 1] -= tmp
                A[l >> 1] += tmp
                l >>= 1
        elif l == r:
            A, N = self.A, self.N
            l += N
            A[l] += x
            while l > 1:
                tmp = SEGMENTTREE_ADD_MAX.max(A[l], A[l ^ 1])
                A[l] -= tmp
                A[l ^ 1] -= tmp
                A[l >> 1] += tmp
                l >>= 1
        elif l < r:
            l += N - 1
            r += N + 1
            while l ^ r ^ 1:
                if ~l & 1:
                    A[l ^ 1] += x
                if r & 1:
                    A[r ^ 1] += x
                tmp = SEGMENTTREE_ADD_MAX.max(A[l], A[l ^ 1])
                A[l] -= tmp
                A[l ^ 1] -= tmp
                A[l >> 1] += tmp
                tmp = SEGMENTTREE_ADD_MAX.max(A[r], A[r ^ 1])
                A[r] -= tmp
                A[r ^ 1] -= tmp
                A[r >> 1] += tmp
                l >>= 1
                r >>= 1
            while l > 1:
                tmp = SEGMENTTREE_ADD_MAX.max(A[l], A[l ^ 1])
                A[l] -= tmp
                A[l ^ 1] -= tmp
                A[l >> 1] += tmp
                l >>= 1

    def query(self, l, r):
        A, N = self.A, self.N
        l += N
        r += N
        S = T = 0
        if l ^ r:
            while l ^ r ^ 1:
                S += A[l]
                T += A[r]
                if ~l & 1:
                    S = SEGMENTTREE_ADD_MAX.max(S, A[l ^ 1])
                if r & 1:
                    T = SEGMENTTREE_ADD_MAX.max(T, A[r ^ 1])
                l >>= 1
                r >>= 1
        S = SEGMENTTREE_ADD_MAX.max(A[l] + S, A[r] + T)
        while l > 1:
            l >>= 1
            S += A[l]
        return S


def solution():
    n, k, A = readis()
    t = SEGMENTTREE_ADD_MAX(k, n)
    E = [[] for _ in range(k + 1)]
    s = 0
    for _ in range(n):
        a, b, c = readis()
        E[k - b].append([a, c])  # Store points in reverse order for y-coordinate
        s += c  # Total sum of all point costs
    dp = 0
    for r in range(k + 1):  # For each row (from bottom to top based on k-b)
        for l, c in E[r]:  # Process all points at the current row
            t.update(0, l, c)  # Update segment tree with point cost
        dp = max(dp, t.A[1] - A * r)  # Compute max profit for current row
        t.update(r, r, dp + r * A)  # Update the segment tree with dp value
    print(s - dp)  # Answer is total cost minus max profit


for i in range(1 if 1 else readi()):
    solution()


# https://github.com/VaHiX/CodeForces/