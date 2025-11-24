# Problem: CF 1681 F - Unique Occurrences
# https://codeforces.com/contest/1681/problem/F

"""
Algorithm: Tree Traversal with Color Tracking
Time Complexity: O(n)
Space Complexity: O(n)

This solution computes the sum of unique edge values on paths between all pairs of vertices in a tree.
The approach uses DFS traversal with parent-child relationships to track edge colors and efficiently calculate
the contribution of each edge value to the final result.
"""

import io
import os
from copy import deepcopy

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline
from collections import deque


def main(t):

    n = int(input())
    neigh = [[] for _ in range(n)]

    colors = [-1] * n
    dic = {}

    # Read edges and build adjacency list
    for _ in range(n - 1):
        u, v, x = map(int, input().split())
        neigh[u - 1].append(v - 1)
        neigh[v - 1].append(u - 1)
        dic[(min(u, v) - 1, max(u, v) - 1)] = x - 1

    children = [[] for _ in range(n)]
    seq = []

    # BFS to build parent-child relationships and assign colors to edges
    queue = deque()
    queue.append(0)
    parent = [-2] * n
    parent[0] = -1

    while queue:
        index = queue.popleft()
        seq.append(index)
        for nextindex in neigh[index]:
            if parent[nextindex] > -2:
                continue
            parent[nextindex] = index
            colors[nextindex] = dic[(min(index, nextindex), max(index, nextindex))]
            children[index].append(nextindex)
            queue.append(nextindex)

    # Build color-based parent-child relationships
    colorchildren = [[] for _ in range(n)]
    colorparent = [-1] * n

    latest = {}

    childrencopy = deepcopy(children)
    stack = []
    latest = {}

    stack.append(0)
    while stack:

        index = stack[-1]
        if childrencopy[index]:
            nextindex = childrencopy[index].pop()
            if colors[nextindex] in latest:
                p = latest[colors[nextindex]]
                colorparent[nextindex] = p
                colorchildren[p].append(nextindex)

            latest[colors[nextindex]] = nextindex
            stack.append(nextindex)

        else:
            stack.pop()
            if index == 0:
                break
            c = colors[index]
            if colorparent[index] < 0:
                del latest[c]
            else:
                latest[c] = colorparent[index]

    # Calculate subtree sizes
    subnum = [0] * n
    ans = 0

    recent = [0] * n

    # Process nodes in reverse order to calculate contributions
    for index in seq[::-1]:

        subnum[index] = 1
        for nextindex in children[index]:
            subnum[index] += subnum[nextindex]

        if index == 0:
            break
        rest = subnum[index]
        for nextindex in colorchildren[index]:
            rest -= subnum[nextindex]

        recent[index] = rest
        for nextindex in colorchildren[index]:
            ans += rest * recent[nextindex]
            recent[nextindex] = 0

    # Handle remaining nodes
    coloralready = {}
    colorleft = {}
    for i in range(n):
        if recent[i] > 0:
            c = colors[i]
            if c not in coloralready:
                coloralready[c] = []
                colorleft[c] = n
            coloralready[c].append(recent[i])
            colorleft[c] -= subnum[i]

    for c in coloralready:
        nums = coloralready[c]
        rest = colorleft[c]
        for num in nums:
            ans += num * rest

    print(ans)


T = 1
t = 1
while t <= T:
    main(t)
    t += 1


# https://github.com/VaHiX/CodeForces/