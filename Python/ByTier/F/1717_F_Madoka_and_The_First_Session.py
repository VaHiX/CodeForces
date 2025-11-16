# Problem: CF 1717 F - Madoka and The First Session
# https://codeforces.com/contest/1717/problem/F

"""
Algorithm: Max Flow Min Cut
This code solves a problem where we need to determine if we can assign operations to pairs of array indices such that 
the final values of array b match the required values in array a, under certain constraints.

The approach:
1. Model the problem as a flow network
2. Create a bipartite graph where:
   - Left nodes represent array indices with s[i] = 1
   - Right nodes represent operation pairs (edges on input)
3. Use max flow algorithm to check if all required changes can be achieved

Time Complexity: O(V * E^2) where V is the number of nodes and E is the number of edges in the flow graph.
Space Complexity: O(V + E) for storing the flow graph and related data structures.
"""

from typing import List, NamedTuple, Optional, cast


class MFGraph:
    class Edge(NamedTuple):
        src: int
        dst: int
        cap: int
        flow: int

    class _Edge:
        def __init__(self, dst: int, cap: int) -> None:
            self.dst = dst
            self.cap = cap
            self.rev: Optional[MFGraph._Edge] = None

    def __init__(self, n: int) -> None:
        self._n = n
        self._g: List[List[MFGraph._Edge]] = [[] for _ in range(n)]
        self._edges: List[MFGraph._Edge] = []

    def add_edge(self, src: int, dst: int, cap: int) -> int:
        assert 0 <= src < self._n
        assert 0 <= dst < self._n
        assert 0 <= cap
        m = len(self._edges)
        e = MFGraph._Edge(dst, cap)
        re = MFGraph._Edge(src, 0)
        e.rev = re
        re.rev = e
        self._g[src].append(e)
        self._g[dst].append(re)
        self._edges.append(e)
        return m

    def get_edge(self, i: int) -> Edge:
        assert 0 <= i < len(self._edges)
        e = self._edges[i]
        re = cast(MFGraph._Edge, e.rev)
        return MFGraph.Edge(re.dst, e.dst, e.cap + re.cap, re.cap)

    def edges(self) -> List[Edge]:
        return [self.get_edge(i) for i in range(len(self._edges))]

    def change_edge(self, i: int, new_cap: int, new_flow: int) -> None:
        assert 0 <= i < len(self._edges)
        assert 0 <= new_flow <= new_cap
        e = self._edges[i]
        e.cap = new_cap - new_flow
        assert e.rev is not None
        e.rev.cap = new_flow

    def flow(self, s: int, t: int, flow_limit: Optional[int] = None) -> int:
        assert 0 <= s < self._n
        assert 0 <= t < self._n
        assert s != t
        if flow_limit is None:
            flow_limit = cast(int, sum(e.cap for e in self._g[s]))

        current_edge = [0] * self._n
        level = [0] * self._n

        def fill(arr: List[int], value: int) -> None:
            for i in range(len(arr)):
                arr[i] = value

        def bfs() -> bool:
            fill(level, self._n)
            queue = []
            q_front = 0
            queue.append(s)
            level[s] = 0
            while q_front < len(queue):
                v = queue[q_front]
                q_front += 1
                next_level = level[v] + 1
                for e in self._g[v]:
                    if e.cap == 0 or level[e.dst] <= next_level:
                        continue
                    level[e.dst] = next_level
                    if e.dst == t:
                        return True
                    queue.append(e.dst)
            return False

        def dfs(lim: int) -> int:
            stack = []
            edge_stack: List[MFGraph._Edge] = []
            stack.append(t)
            while stack:
                v = stack[-1]
                if v == s:
                    flow = min(lim, min(e.cap for e in edge_stack))
                    for e in edge_stack:
                        e.cap -= flow
                        assert e.rev is not None
                        e.rev.cap += flow
                    return flow
                next_level = level[v] - 1
                while current_edge[v] < len(self._g[v]):
                    e = self._g[v][current_edge[v]]
                    re = cast(MFGraph._Edge, e.rev)
                    if level[e.dst] != next_level or re.cap == 0:
                        current_edge[v] += 1
                        continue
                    stack.append(e.dst)
                    edge_stack.append(re)
                    break
                else:
                    stack.pop()
                    if edge_stack:
                        edge_stack.pop()
                    level[v] = self._n
            return 0

        flow = 0
        while flow < flow_limit:
            if not bfs():
                break
            fill(current_edge, 0)
            while flow < flow_limit:
                f = dfs(flow_limit - flow)
                flow += f
                if f == 0:
                    break
        return flow

    def min_cut(self, s: int) -> List[bool]:
        visited = [False] * self._n
        stack = [s]
        visited[s] = True
        while stack:
            v = stack.pop()
            for e in self._g[v]:
                if e.cap > 0 and not visited[e.dst]:
                    visited[e.dst] = True
                    stack.append(e.dst)
        return visited


from sys import stdin

input = lambda: stdin.readline()[:-1]


n, m = map(int, input().split())
s = list(map(int, input().split()))
a = list(map(int, input().split()))
g = MFGraph(n + m + 2)
S = n + m
T = S + 1
tmp = [0] * n
edges = []
edge1 = []
edge2 = []
for i in range(m):
    x, y = map(lambda x: int(x) - 1, input().split())
    tmp[x] += 1
    tmp[y] += 1
    if s[x] == 1 and s[y] == 1:
        edge1.append((x, y, i))
    elif s[x] == 1 or s[y] == 1:
        edge2.append((x, y, i))
    edges.append((x, y))

cnt = 0
for i in range(n):
    if s[i] == 1:
        if a[i] > tmp[i] or (tmp[i] - a[i]) % 2 == 1:
            print("NO")
            exit()
        t = (tmp[i] - a[i]) // 2
        if t != 0:
            g.add_edge(i, T, t)
            cnt += t

for x, y, i in edge1:
    g.add_edge(S, n + i, 1)
    g.add_edge(n + i, x, 1)
    g.add_edge(n + i, y, 1)

ans_flow = g.flow(S, T)
for x, y, i in edge2:
    g.add_edge(S, n + i, 1)
    g.add_edge(n + i, x, 1)
    g.add_edge(n + i, y, 1)
ans_flow += g.flow(S, T)
if ans_flow != cnt:
    print("NO")
    exit()

ans = [-1] * m

for e in g.edges():
    frm = e.src - n
    if 0 <= frm < m:
        to = e.dst
        if e.flow != 0:
            ans[frm] = to

ANS = []
for i in range(m):
    x, y = edges[i]
    if ans[i] != -1:
        if ans[i] == x:
            ANS.append((x, y))
        else:
            ANS.append((y, x))
    else:
        if s[x] == 0:
            ANS.append((x, y))
        elif s[y] == 0:
            ANS.append((y, x))
        else:
            print("NO")
            exit()

print("YES")
for x, y in ANS:
    print(x + 1, y + 1)


# https://github.com/VaHiX/CodeForces/