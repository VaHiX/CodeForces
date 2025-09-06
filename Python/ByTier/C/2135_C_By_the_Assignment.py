# Contest 2135, Problem C: By the Assignment
# URL: https://codeforces.com/contest/2135/problem/C

import sys
input = lambda :sys.stdin.readline()[:-1]
ni = lambda :int(input())
na = lambda :list(map(int,input().split()))
yes = lambda :print("yes");Yes = lambda :print("Yes");YES = lambda : print("YES")
no = lambda :print("no");No = lambda :print("No");NO = lambda : print("NO")
#######################################################################

class LowLink:
    def __init__(self, adj: list[list[int]]):
        self.n = n = len(adj)
        order = [-1] * n
        low = [n] * n
        par = [-1] * n
        children = [[] for _ in range(n)]

        seen = [0] * n
        idx = 0
        for u in range(n):
            if order[u] != -1:
                continue
            seen[u] = 1
            st = [u]
            par[u] = -2
            while st:
                v = st.pop()
                if v >= 0:
                    if order[v] != -1:
                        continue
                    order[v] = idx
                    low[v] = idx
                    idx += 1
                    if v != u:
                        children[par[v]].append(v)
                        st.append(~v)
                    check_p = 0
                    for nv in adj[v]:
                        if nv == par[v] and check_p == 0:
                            check_p += 1
                            continue
                        elif order[nv] != -1:
                            low[v] = min(low[v], order[nv])
                        else:
                            par[nv] = v
                            st.append(nv)
                    continue
                v = ~v
                p = par[v]
                low[p] = min(low[p], low[v])
        self.order = order
        self.low = low
        self.roots = [i for i,v in enumerate(seen) if v]
        self.children = children

    def get_articulation(self) -> list[int]:
        order, low, roots, children = self.order, self.low, self.roots, self.children
        res = [0] * self.n
        for v in range(self.n):
            if v in roots:
                if len(children[v]) >= 2:
                    res[v] = 1
                continue
            for u in children[v]:
                if order[v] <= low[u]:
                    res[v] = 1
                    break
        return res
    
    def get_bridge(self) -> list[tuple[int,int]]:
        order, low, roots, children = self.order, self.low, self.roots, self.children
        res = []
        for v in roots:
            st = [v]
            while st:
                v = st.pop()
                for u in children[v]:
                    if order[v] < low[u]:
                        res.append((v,u))
                    st.append(u)
        return res
    

    def two_edge_connected_components(self) ->  tuple[list[int], list[tuple[int,int]]]:
        order, low, roots, children = self.order, self.low, self.roots, self.children
        
        components = [-1] * self.n
        new_edges = []
        idx = 0
        for v in roots:
            components[v] = idx
            st = [v]
            while st:
                v = st.pop()
                for u in children[v]:
                    if order[v] < low[u]:
                        idx += 1
                        components[u] = idx
                        new_edges.append((components[v], idx))
                    else:
                        components[u] = components[v]
                    st.append(u)
            idx += 1
        return components, new_edges


from collections import defaultdict
 
class UnionFind():
    def __init__(self, n):
        self.n = n
        self.parents = [-1] * n
 
    def find(self, x):
        if self.parents[x] < 0:
            return x
        else:
            self.parents[x] = self.find(self.parents[x])
            return self.parents[x]
 
    def union(self, x, y):
        x = self.find(x)
        y = self.find(y)
 
        if x == y:
            return
 
        if self.parents[x] > self.parents[y]:
            x, y = y, x
 
        self.parents[x] += self.parents[y]
        self.parents[y] = x
 
    def size(self, x):
        return -self.parents[self.find(x)]
 
    def same(self, x, y):
        return self.find(x) == self.find(y)
 
    def members(self, x):
        root = self.find(x)
        return [i for i in range(self.n) if self.find(i) == root]
 
    def roots(self):
        return [i for i, x in enumerate(self.parents) if x < 0]
 
    def group_count(self):
        return len(self.roots())
 
    def all_group_members(self):
        group_members = defaultdict(list)
        for member in range(self.n):
            group_members[self.find(member)].append(member)
        return group_members
 
    def __str__(self):
        return '\n'.join(f'{r}: {m}' for r, m in self.all_group_members().items())


mod = 998244353
for _ in range(ni()):
    n, m, v = na()
    x = na()
    g = [[] for i in range(n)]
    for i in range(m):
        a, b = na()
        a -= 1
        b -= 1
        g[a].append(b)
        g[b].append(a)
    
    LL = LowLink(g)

    b, c = LL.two_edge_connected_components()

    # print(b)
    # print(c)
    uf = UnionFind(n * 2)
    odd = [0] * n
    V = [-1] * n
    cnt = [0] * n
    for i in range(n):
        for j in g[i]:
            if b[i] == b[j]:

                uf.union(i + n, j)
                uf.union(i, j + n)
    
    for i in range(n):
        if uf.same(i, i + n):
            odd[b[i]] = 1
        cnt[b[i]] += 1
        if x[i] != -1:
            if V[b[i]] == -1:
                V[b[i]] = x[i]
            elif V[b[i]] != x[i]:
                print(0)
                break
    else:
        seen = [0] * n
        ans = 1
        # print(odd, V)
        for i in range(n):
            if seen[b[i]]:
                continue
            seen[b[i]] = 1
            if odd[b[i]]:
                if V[b[i]] != -1 and V[b[i]] != 0:
                    print(0)
                    break
            else:
                if V[b[i]] == -1:
                    ans *= v
                    ans %= mod
        else:
            print(ans)