# Problem: CF 720 B - Cactusophobia
# https://codeforces.com/contest/720/problem/B

"""
Algorithm: Edge Cactus Tree Coloring
Approach:
1. Identify cycles in the edge cactus using Union-Find
2. Build a spanning tree using BFS
3. For each cycle, trace back to LCA to find the cycle structure
4. Use Union-Find to group colors that are connected via cycles
5. Maximize number of unique colors in the resulting tree by removing one edge per cycle

Time Complexity: O(m * α(n) + m * log(m)) where α is the inverse Ackermann function
Space Complexity: O(n + m)

Techniques:
- Union-Find with path compression
- Lowest Common Ancestor (LCA) using Range Minimum Query (RMQ)
- BFS for tree construction
- Cycle detection and color grouping
"""

import sys

input = sys.stdin.buffer.readline


def find_root(root_dict, x):
    L = []
    while x != root_dict[x]:
        L.append(x)
        x = root_dict[x]
    for y in L:
        root_dict[y] = x
    return x


class RangeQuery:
    def __init__(self, data, func=min):
        self.func = func
        self._data = _data = [list(data)]
        i, n = 1, len(_data[0])
        while 2 * i <= n:
            prev = _data[-1]
            _data.append([func(prev[j], prev[j + i]) for j in range(n - 2 * i + 1)])
            i <<= 1

    def query(self, begin, end):
        depth = (end - begin).bit_length() - 1
        return self.func(
            self._data[depth][begin], self._data[depth][end - (1 << depth)]
        )


class LCA:
    def __init__(self, root, graph):
        self.time = [-1] * len(graph)
        self.path = [-1] * len(graph)
        P = [-1] * len(graph)
        t = -1
        dfs = [root]
        while dfs:
            node = dfs.pop()
            self.path[t] = P[node]
            self.time[node] = t = t + 1
            for nei, c, i in graph[node]:
                if self.time[nei] == -1:
                    P[nei] = node
                    dfs.append(nei)
        self.rmq = RangeQuery(self.time[node] for node in self.path)

    def __call__(self, a, b):
        if a == b:
            return a
        a = self.time[a]
        b = self.time[b]
        if a > b:
            a, b = b, a
        return self.path[self.rmq.query(a, b)]


def process(n, G):
    m = len(G)
    """
    1. Find "extra" edges, (one for each cycle),
    rest is a tree
    """
    g = [[] for i in range(n + 1)]
    root_dict = [i for i in range(n + 1)]
    total_colors = [0 for i in range(m + 1)]
    cycle_starts = []
    for i in range(m):
        u, v, c = G[i]
        total_colors[c] = 1
        u1 = find_root(root_dict, u)
        v1 = find_root(root_dict, v)
        if u1 == v1:
            cycle_starts.append([u, v, c, i])
        else:
            root_dict[u1] = v1
            g[u].append([v, c, i])
            g[v].append([u, c, i])
    """
    2. BFS tree to find "parents".
    """
    parents = [None for i in range(n + 1)]
    start = [1]
    parents[1] = [-1, -1]
    removed = [0 for i in range(m)]
    while len(start) > 0:
        next_s = []
        for x in start:
            for y, c, i in g[x]:
                if parents[y] is None:
                    parents[y] = [x, c, i]
                    next_s.append(y)
        start = next_s
    """
    3. For each cycle start, trace parents back to LCA,
    this gives the cycle.
    """
    cycles = []
    L = LCA(root=1, graph=g)
    for u, v, c, i in cycle_starts:
        removed[i] = 1
        x = L(u, v)
        cycle = [c]
        L1 = [u]
        while L1[-1] != x:
            x1, c1, i1 = parents[L1[-1]]
            L1.append(x1)
            cycle.append(c1)
            removed[i1] = 1
        L2 = [v]
        while L2[-1] != x:
            x1, c1, i1 = parents[L2[-1]]
            L2.append(x1)
            cycle.append(c1)
            removed[i1] = 1
        cycles.append(cycle)
    """
    4. We now have 
    a) A bunch of cycles
    b) Edges we have to keep.
    
    We have to remove one element from each cycle
    to maximize the
    union of (cycles with removed elements) union (edges we have to keep)
    
    colors are connected if they share a cycle
    if there is a double-connection, or a connection to keep, or a repeat
    can keep all colors in that component
    
    otherwise lose one per cycle
    
    
    """
    m1 = len(cycles)
    total_components = [i for i in range(m + m1 + 1)]
    kept_colors = [0 for i in range(m + 1)]
    answer = sum(total_colors)
    for i in range(m):
        if removed[i] == 0:
            x, y, c = G[i]
            kept_colors[c] = 1
    for i in range(m1):
        for c in cycles[i]:
            i2 = m + 1 + i
            """
            i2 in [m+1, m+m1]
            
            c_root should always be between [1, m]
            """
            c_root = find_root(total_components, c)
            i2_root = find_root(total_components, i2)
            if c_root == i2_root:
                kept_colors[c_root] = 1
            else:
                total_components[i2_root] = c_root
                total_components[c_root] = c_root

    for c in range(1, m + 1):
        c_root = find_root(total_components, c)
        if kept_colors[c] == 1:
            kept_colors[c_root] = 1
    for c in range(1, m + 1):
        c_root = find_root(total_components, c)
        if total_colors[c] == 1 and kept_colors[c_root] != 1:
            kept_colors[c_root] = 1
            answer -= 1
    print(answer)


n, m = [int(x) for x in input().split()]
G = []
for i in range(m):
    u, v, c = [int(x) for x in input().split()]
    G.append([u, v, c])
process(n, G)


# https://github.com/VaHiX/CodeForces/