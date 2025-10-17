# Problem: CF 2107 D - Apple Tree Traversing
# https://codeforces.com/contest/2107/problem/D

"""
D. Apple Tree Traversing

This problem involves finding the lexicographically largest sequence of apple path operations on a tree.

Approach:
- Use Euler tour to traverse the tree in DFS order
- For each node, track the height of its subtrees and compute maximum diameter path through it  
- Greedily select the best path by using a max heap
- Update the tree as apples are removed and push updated nodes back into heap
- The key idea is to always prioritize paths that maximize the lexicographical value

Time Complexity: O(n log n)
Space Complexity: O(n)

Algorithms/Techniques:
- Euler Tour Technique for DFS traversal
- Tree Diameter computation via height tracking
- Max Heap (priority queue) for greedy selection
- Bottom-up Dynamic Programming with post-order processing

"""

import sys
from array import array

input = sys.stdin.readline
import heapq

t = int(input())
for _ in range(t):
    n = int(input())
    p = [array("i", []) for i in range(n + 1)]
    ans = []
    for i in range(n - 1):
        u, v = list(map(int, input().split()))
        p[u].append(v)
        p[v].append(u)
    heitht = [()] * (n + 1)  # Height info for each node
    vis = [0] * (n + 1)      # Visited status for nodes
    pre = [0] * (n + 1)      # Parent tracking
    euler_point = []
    stack = [1]
    while len(stack) > 0:
        u = stack.pop()
        euler_point.append(u)
        for v in p[u]:
            if v == pre[u]:
                continue
            pre[v] = u
            stack.append(v)
    point_max = [()] * (n + 1)

    def update(a):
        # Collect heights of unvisited children
        below_a = [heitht[v] for v in p[a] if v != pre[a] and vis[v] == 0]
        below_a.sort()
        if len(below_a) == 0:
            heitht[a] = (1, a)
            point_max[a] = (1, a, a)
            return
        elif len(below_a) == 1:
            h_v, v = below_a[0]
            heitht[a] = (h_v + 1, v)
            point_max[a] = (h_v + 1, max(a, v), min(a, v))
            return
        h_v1, v1 = below_a[-1]
        h_v2, v2 = below_a[-2]
        heitht[a] = (h_v1 + 1, v1)
        point_max[a] = (h_v1 + h_v2 + 1, max(v1, v2), min(v1, v2))

    heap = []
    for u in reversed(euler_point):
        update(u)
        x, y, z = point_max[u]
        heapq.heappush(heap, (-x, -y, -z, u))
    seg = []
    while len(heap) > 0:
        d, u, v, a = heapq.heappop(heap)
        d, u, v = -d, -u, -v
        if vis[a]:
            continue
        if (d, u, v) != point_max[a]:
            continue
        seg.append((d, u, v))
        for now in (u, v):
            while now != a:
                vis[now] = 1
                now = pre[now]
        vis[a] = 1
        now = pre[a]
        while now and vis[now] == 0:
            update(now)
            heapq.heappush(
                heap, (-point_max[now][0], -point_max[now][1], -point_max[now][2], now)
            )
            now = pre[now]
    seg.sort()
    for i in range(len(seg) - 1, -1, -1):
        for x in seg[i]:
            print(x, end=" ")
    print()


# https://github.com/VaHiX/codeForces/