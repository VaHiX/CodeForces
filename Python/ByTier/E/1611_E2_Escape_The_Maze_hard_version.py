# Problem: CF 1611 E2 - Escape The Maze (hard version)
# https://codeforces.com/contest/1611/problem/E2

"""
Code Purpose:
This code solves the "Escape The Maze" problem where Vlad (the player) tries to escape a tree maze while being chased by friends.
The goal is to determine the minimum number of friends that must remain in the maze to guarantee catching Vlad before he escapes.
It uses a BFS-based approach, simulating the movement of Vlad and friends through the tree.
Algorithm:
1. Build the tree from the input corridors
2. Initialize BFS with Vlad at room 1 and friends at their specified rooms
3. Simulate movement where Vlad and friends move simultaneously
4. If Vlad reaches a leaf node (degree 1, not root), he wins -> return -1
5. If friends can intercept Vlad's path before he escapes, count minimum friends needed

Time Complexity: O(N) - Each node is visited at most once
Space Complexity: O(N) - For adjacency list and label array
"""

import sys

ipt = sys.stdin.readline
from collections import deque

inf = 1 << 30
for _ in range(int(ipt())):
    input()  # Read empty line
    N, K = map(int, ipt().split())
    X = list(map(int, ipt().split()))
    G = [[] for _ in range(N)]
    for _ in range(N - 1):
        u, v = map(int, ipt().split())
        u, v = u - 1, v - 1
        G[u].append(v)
        G[v].append(u)

    dq = deque()
    label = [-1] * N  # label[i] stores which friend (or Vlad) is closest to node i
    dq.append((0, 0))  # Vlad starts at node 0 (room 1)
    label[0] = 0
    for x in X:
        dq.append((x - 1, x - 1))  # Add friends to BFS queue with label = their room number
        label[x - 1] = x - 1

    ans = 0
    while dq:
        cur, l = dq.pop()  # cur = current node, l = label of entity at this node
        
        # If Vlad reaches a leaf node (not root) and is not blocked, he wins
        if cur != 0 and len(G[cur]) == 1 and l == 0:
            ans = -1
            break

        # Visit neighbors
        for nxt in G[cur]:
            if label[nxt] == -1:  # If node not visited yet
                label[nxt] = l  # Assign same label to next node
                dq.appendleft((nxt, l))  # Add to front of queue (BFS)
            else:
                # If someone else is already at this node
                if l == 0 and label[nxt]:  # Vlad encounters someone else
                    ans += 1  # Increment friend count

    print(ans)


# https://github.com/VaHiX/CodeForces/