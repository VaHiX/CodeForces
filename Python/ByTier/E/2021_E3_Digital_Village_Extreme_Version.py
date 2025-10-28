# Problem: CF 2021 E3 - Digital Village (Extreme Version)
# https://codeforces.com/contest/2021/problem/E3

"""
Code Purpose:
This solution addresses the problem of placing servers in a village (represented as a graph) to minimize total latency for houses requiring internet.
It uses a Minimum Spanning Tree (MST) approach with a Disjoint Set Union (DSU) data structure to efficiently manage connected components and compute optimal server placements.

Algorithms:
- Minimum Spanning Tree (Kruskal's algorithm with DSU)
- Disjoint Set Union (DSU) with path compression and union by rank
- Prefix sum technique for efficient computation of cumulative costs

Time Complexity: O(m * log(m) + n * log(n))
Space Complexity: O(n + m)

Where:
- m is the number of edges (cables)
- n is the number of nodes (houses)
"""

def solve():
    import sys

    data = sys.stdin.buffer.read().split()
    if not data:
        return
    it = iter(data)
    t = int(next(it))

    class DSU:
        __slots__ = ("parent", "req", "cost", "rank", "rep")

        def __init__(self, n):
            self.parent = list(range(n))
            self.req = [0] * n
            self.cost = [0] * n
            self.rank = [0] * n
            self.rep = [-1] * n

        def find(self, a):
            # Find root with path compression
            while self.parent[a] != a:
                self.parent[a] = self.parent[self.parent[a]]
                a = self.parent[a]
            return a

        def union(self, a, b, w, extras):
            # Union two components and update cost
            if a == b:
                return a
            # Union by rank
            if self.rank[a] < self.rank[b]:
                a, b = b, a
            self.parent[b] = a
            newReq = self.req[a] + self.req[b]
            if self.req[a] > 0 and self.req[b] > 0:
                # Calculate cost of connecting two components
                cand1 = self.cost[a] + w * self.req[b]
                cand2 = self.cost[b] + w * self.req[a]
                newCost = cand1 if cand1 < cand2 else cand2
                extra = newCost - (self.cost[a] + self.cost[b])
                extras.append(extra)
            else:
                newCost = self.cost[a] + self.cost[b]
            self.req[a] = newReq
            self.cost[a] = newCost
            if self.rep[a] == -1:
                self.rep[a] = self.rep[b]
            return a

    out_list = []
    for _ in range(t):
        n = int(next(it))
        m = int(next(it))
        p = int(next(it))
        req_list = [int(next(it)) - 1 for _ in range(p)]
        isReq = [False] * n
        for x in req_list:
            isReq[x] = True
        edges = []
        for i in range(m):
            u = int(next(it)) - 1
            v = int(next(it)) - 1
            w = int(next(it))
            edges.append((w, u, v))
        edges.sort(key=lambda x: x[0])  # Sort edges by weight (latency)
        dsu = DSU(n)
        for i in range(n):
            if isReq[i]:
                dsu.req[i] = 1
                dsu.cost[i] = 0
                dsu.rep[i] = i
            else:
                dsu.req[i] = 0
                dsu.cost[i] = 0
                dsu.rep[i] = -1
        extras = []
        treeEdges = []
        for w, u, v in edges:
            ru = dsu.find(u)
            rv = dsu.find(v)
            if ru == rv:
                continue
            repu = dsu.rep[ru]
            repv = dsu.rep[rv]
            if repu != -1 and repv != -1:
                treeEdges.append((repu, repv, w))
            dsu.union(ru, rv, w, extras)
        for i in range(n):
            if dsu.req[dsu.find(i)] == p:
                base = dsu.cost[dsu.find(i)]
                break
        extras.sort(reverse=True)  # Sort in descending order for prefix sum
        pref = [0]
        for ex in extras:
            pref.append(pref[-1] + ex)
        ans = [0] * n
        for k in range(1, p + 1):
            if k - 1 < len(pref):
                val = base - pref[k - 1]
            else:
                val = 0
            ans[k - 1] = val
        for k in range(p, n):
            ans[k] = 0
        out_list.append(" ".join(str(x) for x in ans))
    sys.stdout.write("\n".join(out_list))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/