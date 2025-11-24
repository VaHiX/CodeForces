# Problem: CF 2106 G2 - Baudelaire (hard version)
# https://codeforces.com/contest/2106/problem/G2

"""
Interactive problem to determine node values in a tree.

Algorithm:
- Use centroid decomposition to identify the root of the tree.
- For each centroid, perform binary search on its neighbors to locate the root.
- Once root is identified, propagate values using query_sum and toggle operations.
- Time Complexity: O(n^2) in worst case, but optimized by centroid decomposition.
- Space Complexity: O(n)

Key Techniques:
- Centroid decomposition
- Binary search for identifying root among children of centroid
- Propagation based on path sums from root
"""

def answer(values):
    print(f"! {' '.join(map(str, values))}", flush=True)


def query_sum(nodes):
    global cnt
    cnt += 1
    print(f"? 1 {len(nodes)} {' '.join(map(str, nodes))}", flush=True)
    return int(input())


def toggle(u):
    global cnt
    cnt += 1
    print(f"? 2 {u}", flush=True)


ans = 1e100
center = -1
cnt = 0
actives = 0
for ii in range(int(input())):
    n = int(input())
    cnt = 0
    actives = n
    ans = actives
    center = -1
    edges = []
    for i in range(n - 1):
        u, v = map(int, input().split())
        edges.append((u, v))
    g = [[] for _ in range(n + 1)]
    og = [[] for _ in range(n + 1)]
    for u, v in edges:
        g[u].append(v)
        g[v].append(u)
        og[u].append(v)
        og[v].append(u)

    def dfs(u, fa, sz, ns):
        global ans, center
        sz[u] = 1
        max_part = 0
        for v in g[u]:
            if v == fa:
                continue
            dfs(v, u, sz, ns)
            sz[u] += sz[v]
            max_part = max(max_part, sz[v])
        max_part = max(max_part, ns - sz[u])
        if max_part < ans:
            ans = max_part
            center = u

    def inactive(u, father):
        global actives
        actives -= 1
        for v in g[u]:
            if v == father:
                continue
            inactive(v, u)

    def setresult(curr, father, fav, res):
        fcurr = query_sum([curr])
        v = fcurr - fav
        res[curr] = v
        for neigh in og[curr]:
            if neigh != father:
                setresult(neigh, curr, fcurr, res)

    start = n - 1
    father = 0
    root = -1
    while True:
        ans = actives
        center = -1
        dfs(start, father, [0] * (n + 1), actives)
        neigh = []
        for v in g[center]:
            if v != father:
                neigh.append(v)
        l = 0
        r = len(neigh) - 1
        if len(neigh) == 0:
            root = center
            break
        if len(neigh) == 1:
            bsv = query_sum([neigh[0], center])
            toggle(center)
            asv = query_sum([neigh[0], center])
            if abs(bsv - asv) == 4:
                root = center
                break
        else:
            mid = (l + r) // 2
            bs1 = query_sum([neigh[i] for i in range(l, r + 1)])
            toggle(center)
            as1 = query_sum([neigh[i] for i in range(l, r + 1)])
            if abs(as1 - bs1) == (r - l + 1) * 2:
                root = center
                break
            while l < r:
                mid = (l + r) // 2
                bs1 = query_sum([neigh[i] for i in range(l, mid + 1)])
                toggle(center)
                as1 = query_sum([neigh[i] for i in range(l, mid + 1)])
                diff1 = abs(bs1 - as1)
                s1sum = mid - l + 1
                if diff1 == s1sum * 2:
                    l = mid + 1
                else:
                    r = mid
        for i in range(len(g[neigh[l]])):
            if g[neigh[l]][i] == center:
                del g[neigh[l]][i]
                break
        inactive(center, neigh[l])
        father = center
        start = neigh[l]
    res = [0] * (n + 1)
    setresult(root, 0, 0, res)
    answer(res[1:])


# https://github.com/VaHiX/codeForces/