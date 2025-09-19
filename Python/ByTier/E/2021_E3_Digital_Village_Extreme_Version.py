# Contest 2021, Problem E3: Digital Village (Extreme Version)
# URL: https://codeforces.com/contest/2021/problem/E3

# YOUR CODE HERE
import sys
# sys.setrecursionlimit(10**6)

def solve():
    import sys
    data = sys.stdin.buffer.read().split()
    if not data:
        return
    it = iter(data)
    t = int(next(it))
    out_lines = []
    # DSU structure with extra state.
    class DSU:
        __slots__ = ('parent','req','cost','rank','rep')
        def __init__(self, n):
            self.parent = list(range(n))
            self.req = [0]*n      # number of required nodes in component
            self.cost = [0]*n     # optimal one–facility cost for the required nodes in component
            self.rank = [0]*n
            self.rep = [-1]*n     # a representative required node (or -1 if none)
        def find(self, a):
            while self.parent[a]!=a:
                self.parent[a] = self.parent[self.parent[a]]
                a = self.parent[a]
            return a
        def union(self, a, b, w, extras):
            if a == b:
                return a
            if self.rank[a] < self.rank[b]:
                a, b = b, a
            self.parent[b] = a
            newReq = self.req[a] + self.req[b]
            if self.req[a] > 0 and self.req[b] > 0:
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
        req_list = [int(next(it))-1 for _ in range(p)]
        isReq = [False]*n
        for x in req_list:
            isReq[x] = True
        edges = []
        for i in range(m):
            u = int(next(it))-1
            v = int(next(it))-1
            w = int(next(it))
            edges.append((w, u, v))
        edges.sort(key = lambda x: x[0])
        
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
        
        extras = []  # extra–cost for each merge where both sides had required nodes.
        treeEdges = []  # auxiliary: tree edges connecting required–reps (not used further).
        for w,u,v in edges:
            ru = dsu.find(u)
            rv = dsu.find(v)
            if ru == rv:
                continue
            repu = dsu.rep[ru]
            repv = dsu.rep[rv]
            if repu != -1 and repv != -1:
                treeEdges.append((repu, repv, w))
            newroot = dsu.union(ru, rv, w, extras)
        # base = optimal one–facility cost for all required nodes.
        for i in range(n):
            if dsu.req[dsu.find(i)] == p:
                base = dsu.cost[ dsu.find(i) ]
                break
        extras.sort(reverse=True)
        pref = [0]
        for ex in extras:
            pref.append(pref[-1] + ex)
        ans = [0]*n
        for k in range(1, p+1):
            if k-1 < len(pref):
                val = base - pref[k-1]
            else:
                val = 0
            ans[k-1] = val
        for k in range(p, n):
            ans[k] = 0
        out_list.append(" ".join(str(x) for x in ans))
    sys.stdout.write("\n".join(out_list))

if __name__=="__main__":
    solve()
# END OF SOLUTION