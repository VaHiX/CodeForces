# Problem: CF 2134 D - Sliding Tree
# https://codeforces.com/contest/2134/problem/D

"""
D. Sliding Tree

Purpose:
This code solves the problem of transforming a given tree into a path graph using "sliding" operations.
A sliding operation selects three vertices a, b, c such that b is connected to both a and c, then it moves 
the neighbors of b (excluding a and c) to be directly connected to c instead.

The algorithm uses:
1. Finding the diameter of the tree through two DFS traversals
2. Identifying a vertex on the diameter as an endpoint
3. Backtracking to find a suitable candidate for a sliding operation

Time Complexity: O(n) per test case, since each node is visited at most twice (once for each DFS)
Space Complexity: O(n), for storing the adjacency list and auxiliary data structures.

"""
import sys
from collections import defaultdict

input = lambda: sys.stdin.readline().rstrip()
li = lambda: list(map(int, input().split()))
mii = lambda: map(int, input().split(" "))
ii = lambda: int(input())
if __name__ == "__main__":
    t = ii()
    for tr in range(t):
        n = ii()
        graph = defaultdict(list)
        for i in range(n - 1):
            a, b = mii()
            graph[a].append(b)
            graph[b].append(a)
        if n == 1 or n == 2:
            print(-1)
        else:

            def dfs(curr):
                stk = [(curr, -1, 0)]
                global n
                dist = [0] * (n + 1)
                max_dis = 0
                max_node = None
                while len(stk) > 0:
                    top, par, dis = stk.pop()
                    dist[top] = dis
                    if max_dis < dis:
                        max_dis = dis
                        max_node = top
                    for child in graph[top]:
                        if child != par:
                            stk.append((child, top, dis + 1))
                return max_node, dist

            node, dist = dfs(1)
            node2, dist = dfs(node)
            dia = max(dist)
            if dia == n - 1:
                print(-1)
            else:
                stk = []
                path = set()
                stk.append((node2, -1))
                a = None
                b = None
                c = None
                while len(stk) > 0:
                    top, par = stk.pop()
                    for ch in graph[top]:
                        if ch != par and dist[ch] + 1 == dist[top]:
                            stk.append((ch, top))
                            path.add(ch)
                    if par != -1 and len(graph[top]) > 2:
                        a = par
                        b = top
                        for ch in graph[top]:
                            if ch != a and ch != b and ch not in path:
                                c = ch
                                break
                        break
                print(f"{a} {b} {c}")


# https://github.com/VaHiX/codeForces/