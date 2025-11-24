# Problem: CF 2109 D - D/D/D
# https://codeforces.com/contest/2109/problem/D

"""
D. D/D/D
Algorithms/Techniques: BFS on bipartite graph, precomputation of maximum even/odd sums.

Time Complexity:
O(n + m + ℓ) per test case, where n is number of vertices, m is number of edges, and ℓ is size of multiset.
This is because we do BFS in O(n + m), and process the elements of A once for precomputation in O(ℓ).

Space Complexity:
O(n + m + ℓ) per test case. We store adjacency list (O(n + m)), distance array (O(n)),  
and the multiset A (O(ℓ)).

Problem Description:
For a graph with n nodes and m edges, and a multiset of ℓ integers (A), determine for each node
whether it's reachable from node 1 using moves where:
- You pick an integer k from A
- Traverse exactly k edges in the graph
The walk can reuse vertices, and you must use one copy of each value in A.

Key Observations:
- The parity of steps matters; each step has a length of k.
- So we track distances modulo 2: even-length walks and odd-length walks.
- For each node u, we compute the minimum number of steps (mod 2) to reach it.
- Then, for each possible sum in multiset A:
    - If total sum is even, maximum even sum from A can make it reachable if distance <= max_even
    - Otherwise, max odd sum can be used.
"""

import sys

input = lambda: sys.stdin.readline().rstrip()
ii = lambda: int(input())
mii = lambda: map(int, input().split())
lii = lambda: list(mii())
from collections import deque

inf = 10**18


def solve():
    n, m, l = mii()
    arr = lii()  # Multiset A
    tot = sum(arr)
    mxeven, mxodd = 0, -1  # Max even and odd sums from the multiset
    mnodd = min((x for x in arr if x & 1), default=-1)  # Minimum odd element of A
    if tot % 2 == 0:
        mxeven = tot
        if mnodd > 0:
            mxodd = tot - mnodd  # Subtract the smallest odd to get max odd sum
    else:
        mxodd = tot
        if mnodd > 0:
            mxeven = tot - mnodd  # Subtract the smallest odd to get max even sum

    g = [[] for _ in range(n)]
    for _ in range(m):
        u, v = mii()
        u -= 1
        v -= 1
        g[u].append(v)
        g[v].append(u)

    # BFS to find min distance from vertex 0 (mod 2) for even and odd steps
    dis = [[inf] * n for _ in range(2)]
    dis[0][0] = 0  # Distance from vertex 0, with even number of steps (so we start at even)
    dq = deque([(0, 0)])
    while dq:
        d, u = dq.popleft()
        for v in g[u]:
            # Toggle parity since each edge adds one step
            if d + 1 < dis[d & 1 ^ 1][v]:
                dis[d & 1 ^ 1][v] = d + 1
                dq.append((d + 1, v))

    ans = [0] * n
    for u in range(n):
        # Check if we can reach node u using even or odd steps (based on reachable sums)
        if mxeven >= dis[0][u] or mxodd >= dis[1][u]:
            ans[u] = 1
    return "".join(map(str, ans))


for _ in range(ii()):
    print(solve())


# https://github.com/VaHiX/codeForces/