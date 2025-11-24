# Problem: CF 1827 D - Two Centroids
# https://codeforces.com/contest/1827/problem/D

"""
Code Purpose:
This code solves the problem of finding the minimum number of operations to make a tree have two centroids after each addition of a vertex. 
It uses a combination of tree traversal (DFS), binary indexed tree (BIT) for efficient range queries and updates, and centroid tracking techniques.

Algorithms/Techniques:
- DFS traversal with Euler tour technique to process tree structure
- Binary Indexed Tree (Fenwick Tree) for efficient prefix sum queries and updates
- Centroid tracking logic to determine when a tree has two centroids
- Level ancestor binary search to find specific ancestors in the tree

Time Complexity: O(N log N) per test case, where N is the number of nodes
Space Complexity: O(N) for storing tree structure, BIT, and auxiliary arrays

The problem involves building a tree incrementally and determining the minimum number of edge additions to create two centroids in the resulting tree at each step.
"""

import sys

input = lambda: sys.stdin.buffer.readline()
mi = lambda: map(int, input().split())
li = lambda: list(mi())


class BIT:
    def __init__(self, n, mod=0):
        self.BIT = [0] * (n + 1)
        self.num = n
        self.mod = mod

    """
    return A[1] + A[2] + ... A[idx] in O(log n)
    """

    def query(self, idx):
        res_sum = 0
        mod = self.mod
        while idx > 0:
            res_sum += self.BIT[idx]
            if mod:
                res_sum %= mod
            idx -= idx & (-idx)
        return res_sum

    """
    A[idx] += in O(log n)
    """

    def update(self, idx, x):
        mod = self.mod
        while idx <= self.num:
            self.BIT[idx] += x
            if mod:
                self.BIT[idx] %= mod
            idx += idx & (-idx)
        return


for _ in range(int(input())):
    N = int(input())
    parent = [-1] + [int(p) - 1 for p in input().split()]
    edge = [[] for v in range(N)]
    for v in range(1, N):
        edge[parent[v]].append(v)

    begin = [-1] * N
    end = [-1] * N
    begin[0] = 1
    next_idx = 2
    stack = [0]
    cnt = [0] * N
    while stack:
        v = stack[-1]
        if len(edge[v]) == cnt[v]:
            end[v] = next_idx
            next_idx += 1
            stack.pop()
            continue
        nv = edge[v][cnt[v]]
        cnt[v] += 1
        begin[nv] = next_idx
        next_idx += 1
        stack.append(nv)

    fw = BIT(2 * N)

    p, q = 0, 1
    fw.update(begin[0], 1)
    fw.update(begin[1], 1)
    two_centroid = True

    def level_ancestor(v, c):
        ok = 0
        ng = len(edge[v])
        while ng - ok > 1:
            mid = (ok + ng) // 2
            check = edge[v][mid]

            if begin[check] < begin[c]:
                ok = mid
            else:
                ng = mid
        return edge[v][ok]

    ans = [0]
    for v in range(2, N):

        fw.update(begin[v], 1)
        if not two_centroid:
            if begin[p] <= begin[v] < end[p]:
                LA = level_ancestor(p, v)

                if begin[p] <= begin[q] < end[p]:
                    now_max = fw.query(end[q]) - fw.query(begin[q] - 1)
                else:
                    now_max = v + 1 - (fw.query(end[p]) - fw.query(begin[p] - 1))
                new_max = fw.query(end[LA]) - fw.query(begin[LA] - 1)
                if now_max < new_max:
                    q = LA
                    ans.append(v + 1 - 2 * new_max)
                    if v + 1 == 2 * new_max:
                        two_centroid = True
                else:
                    ans.append(v + 1 - 2 * now_max)
                    if v + 1 == 2 * now_max:
                        two_centroid = True
            else:
                if begin[p] <= begin[q] < end[p]:
                    now_max = fw.query(end[q]) - fw.query(begin[q] - 1)
                else:
                    now_max = v + 1 - (fw.query(end[p]) - fw.query(begin[p] - 1))
                new_max = v + 1 - (fw.query(end[p]) - fw.query(begin[p] - 1))

                if now_max < new_max:
                    q = parent[p]
                    ans.append(v + 1 - 2 * new_max)
                    if v + 1 == 2 * new_max:
                        two_centroid = True
                else:
                    ans.append(v + 1 - 2 * now_max)
                    if v + 1 == 2 * now_max:
                        two_centroid = True
            continue

        if parent[p] == q:
            p, q = q, p

        if begin[q] <= begin[v] < end[q]:
            p, q = q, p
        ans.append(1)
        two_centroid = False

    print(*ans)


# https://github.com/VaHiX/CodeForces/