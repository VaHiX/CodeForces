# Problem: CF 1975 D - Paint the Tree
# https://codeforces.com/contest/1975/problem/D

"""
Algorithm: Tree BFS traversal with two-phase approach
    - First phase: Simulate P_A and P_B movements to find minimum steps to "overlap" 
      where P_B can paint all remaining white nodes blue
    - Second phase: For the overlapping node, find the farthest node to compute 
      the maximum number of steps needed to paint the whole tree blue

Time Complexity: O(n) per test case, since each node is visited a constant number of times
Space Complexity: O(n) for storing the graph and BFS queues

Approach:
1. Build adjacency list representation of tree
2. Run BFS from both starting points (a and b) to find minimum steps where 
   P_B can reach a red node (so it can paint it blue)
3. Once overlap is found, compute max distance from that overlap node to all 
   neighbors to simulate painting the rest of the tree efficiently
"""

import collections
import sys

input = sys.stdin.readline


def solve():
    n = int(input())
    a, b = map(int, input().split())
    g = [[] for _ in range(n)]
    for _ in range(n - 1):
        x, y = map(int, input().split())
        x -= 1
        y -= 1
        g[x].append(y)
        g[y].append(x)
    a -= 1
    b -= 1

    if n == 1:
        print(0)
        return

    # Phase 1: Find minimum steps to get P_B to a red node
    def check(a, b, g):
        vis = [0] * n  # 0=unvisited, 1=P_A's region, 2=P_B's region
        vis[a] = 1
        vis[b] = 2
        step = 1
        qa = collections.deque()
        qb = collections.deque()
        qa.append(a)
        qb.append(b)
        while qa and qb:
            for _ in range(len(qa)):
                i = qa.popleft()
                for j in g[i]:
                    if vis[j] == 0:  # Node not yet visited
                        qa.append(j)
                        vis[j] = 1  # Mark as visited by P_A
            for _ in range(len(qb)):
                i = qb.popleft()
                for j in g[i]:
                    if vis[j] == 1:  # Node was visited by P_A
                        # This means P_B can paint this node blue
                        return step, j
                    if vis[j] == 0:
                        vis[j] = 2  # Mark as visited by P_B
                        qb.append(j)
            step += 1

    if a != b:
        step, node = check(a, b, g)
    else:
        step, node = 0, a

    # Phase 2: Compute max distance from the overlap node to neighbors
    vis = [True] * n

    def find_d(i, j):
        vis[i] = False
        vis[j] = False
        cnt = 0
        q = collections.deque()
        q.append(j)
        d = 0
        while q:
            for _ in range(len(q)):
                i = q.popleft()
                for j in g[i]:
                    if vis[j]:
                        vis[j] = False
                        q.append(j)
                        cnt += 1
            d += 1
        return d

    res = 2 * n
    for j in g[node]:  # For neighbors of overlap node
        res = min(res, 2 * (n - 1) - find_d(node, j))
    print(step + res)


t = int(input())
for _ in range(t):
    solve()


# https://github.com/VaHiX/CodeForces/