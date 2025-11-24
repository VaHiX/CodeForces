# Problem: CF 1702 G1 - Passable Paths (easy version)
# https://codeforces.com/contest/1702/problem/G1

"""
Algorithm/Techniques: 
DFS traversal with post-order processing to check if a set of vertices forms a path in a tree.
Time Complexity: O(n + sum of k over all queries) where n is number of vertices and sum of k is total number of vertices across all queries.
Space Complexity: O(n) for adjacency list and auxiliary arrays.

The problem is about determining whether a given set of vertices in a tree forms a connected path.
This is done by:
1. Performing a DFS traversal to compute subtree sizes
2. For each query, we check if there's at most one vertex in the set that has more than one child in the subtree
3. We also make sure if the total count of vertices in the set is the sum of all subtree counts, then only 1 or 2 edges are involved to make a path.
"""

def maximum(a, b):
    return max(a, b)


def minimum(a, b):
    return min(a, b)


def leftshift(a):
    return a << 1


def INPUT():
    return int(input())


def GINPUT():
    return input()


def MAPINPUT():
    return map(int, input().split())


def LIST_INPUT():
    return list(map(int, input().split()))



S = lambda: input().rstrip()
I = lambda: int(S())
M = lambda: map(int, S().split())
L = lambda: list(M())
from collections import deque

I = input
R = lambda: map(int, I().split())
anuvab, udayon = 0, 0
amrita = 0


def f(x, pre):
    global flg
    dp = [0] * (n + 1)
    q = deque([(x, pre)])
    R = []
    while q:
        u, p = q.popleft()
        R.append((u))
        for v in g[u]:
            if v != p:
                q.append((v, u))
    for u in R[::-1]:
        path = 0
        dp[u] += 1 if u in s else 0
        for v in g[u]:
            path += 1 if dp[v] else 0
            dp[u] += dp[v]
        flg = flg and (path <= 1 or path == 2 and k == dp[u])
    return dp[x]


n = int(I())
g = [[] for _ in range(n + 1)]
for _ in [0] * (n - 1):
    u, v = R()
    g[u].append(v)
    g[v].append(u)
for _ in [0] * int(I()):
    k = int(I())
    flg = 1
    s = set(R())
    f(1, 0)
    print(["NO", "YES"][flg])


# https://github.com/VaHiX/CodeForces/