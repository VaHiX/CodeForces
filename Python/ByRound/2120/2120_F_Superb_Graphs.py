# Problem: CF 2120 F - Superb Graphs
# https://codeforces.com/contest/2120/problem/F

# F. Superb Graphs
# Time complexity: O(n^2 * k + m) where m is total number of edges across all graphs
# Space complexity: O(n^2 + m)
# Algorithm: This solution uses a 2-SAT approach to determine if there exists a valid assignment of vertices to independent sets or cliques.
# Key idea:
# - For each vertex in the input graph, we create two boolean variables (true = independent set, false = clique)
# - We use implication edges in a directed graph to enforce constraints (if vertex maps to clique in one graph, it cannot map to clique in another)
# - We perform Kosaraju's algorithm for finding strongly connected components (SCCs) 
# - If any vertex and its negation belong to same SCC, then the problem is unsatisfiable

def solve():
    n, m = map(int, input().split())
    nn = 2 * n
    v1 = [[] for i in range(nn)]
    v2 = [[] for i in range(nn)]
    wow = 300

    def id(x, y):
        return 2 * x + (0 if y else 1)

    # Process each of the k graphs
    for i in range(m):
        a = [0] * wow
        k = int(input())
        for j in range(k):
            u, v = map(int, input().split())
            u -= 1
            v -= 1
            a[u] |= 1 << v
            a[v] |= 1 << u
        # For each pair of vertices x and y where they have same neighbors (excluding themselves)
        for x in range(n):
            for y in range(x + 1, n):
                ax = a[x] & ~(1 << x) & ~(1 << y)
                ay = a[y] & ~(1 << x) & ~(1 << y)
                if ax != ay:
                    continue
                c = (a[x] >> y) & 1
                # Add implication edges to enforce constraints
                if c:
                    f1, f2 = id(x, True), id(y, False)
                    v1[f1].append(f2)
                    v2[f2].append(f1)
                    f11, f22 = id(y, True), id(x, False)
                    v1[f11].append(f22)
                    v2[f22].append(f11)
                else:
                    f1, f2 = id(x, False), id(y, True)
                    v1[f1].append(f2)
                    v2[f2].append(f1)
                    f11, f22 = id(y, False), id(x, True)
                    v1[f11].append(f22)
                    v2[f22].append(f11)
    vi = [False] * nn
    v3 = []

    # DFS to find topological order - first phase of Kosaraju's algorithm
    def df1(u):
        vi[u] = True
        for it in v1[u]:
            if not vi[it]:
                df1(it)
        v3.append(u)

    for i in range(nn):
        if not vi[i]:
            df1(i)
    cm = [-1] * nn
    c1 = 0

    # DFS to find SCCs - second phase of Kosaraju's algorithm
    def df2(u):
        nonlocal c1
        cm[u] = c1
        for it in v2[u]:
            if cm[it] == -1:
                df2(it)

    for i in range(nn - 1, -1, -1):
        u = v3[i]
        if cm[u] == -1:
            df2(u)
            c1 += 1
    ok = True
    # Check if any vertex and its negation are in the same SCC => contradiction
    for i in range(n):
        if cm[id(i, True)] == cm[id(i, False)]:
            ok = False
            break
    print("YES" if ok else "NO")


t = int(input())
for z in range(t):
    solve()


# https://github.com/VaHiX/CodeForces/