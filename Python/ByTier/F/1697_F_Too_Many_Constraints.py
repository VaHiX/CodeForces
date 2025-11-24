# Problem: CF 1697 F - Too Many Constraints
# https://codeforces.com/contest/1697/problem/F

"""
Two-Satisfiability (2-SAT) solution for building a non-decreasing array with constraints.

Algorithms:
- 2-SAT using Kosaraju's algorithm for strongly connected components
- Transforming array constraints into 2-SAT clauses
- Using implication graph to check satisfiability

Time Complexity: O(n * k + m) where n is array length, k is value range, m is constraints
Space Complexity: O(n * k + m) for storing the implication graph and auxiliary data

The approach:
1. Convert array element constraints into boolean variables (a[i] = j)
2. Add constraints for:
   - Value exclusions (a[i] != x)
   - Sum constraints (a[i] + a[j] <= x or a[i] + a[j] >= x)
   - Non-decreasing property (a[i] <= a[i+1])
3. Solve 2-SAT problem to find valid assignment
4. Translate back to actual array values
"""

def two_sat(n, clause):
    answer = [0] * n
    edges = []
    N = 2 * n
    for s in clause:
        i, f, j, g = s
        edges.append((2 * i + (0 if f else 1), 2 * j + (1 if g else 0)))
        edges.append((2 * j + (0 if g else 1), 2 * i + (1 if f else 0)))
    M = len(edges)
    start = [0] * (N + 1)
    elist = [0] * M
    for e in edges:
        start[e[0] + 1] += 1
    for i in range(1, N + 1):
        start[i] += start[i - 1]
    counter = start[:]
    for e in edges:
        elist[counter[e[0]]] = e[1]
        counter[e[0]] += 1
    visited = []
    low = [0] * N
    Ord = [-1] * N
    ids = [0] * N
    NG = [0, 0]

    def dfs(v):
        stack = [(v, -1, 0), (v, -1, 1)]
        while stack:
            v, bef, t = stack.pop()
            if t:
                if bef != -1 and Ord[v] != -1:
                    low[bef] = min(low[bef], Ord[v])
                    stack.pop()
                    continue
                low[v] = NG[0]
                Ord[v] = NG[0]
                NG[0] += 1
                visited.append(v)
                for i in range(start[v], start[v + 1]):
                    to = elist[i]
                    if Ord[to] == -1:
                        stack.append((to, v, 0))
                        stack.append((to, v, 1))
                    else:
                        low[v] = min(low[v], Ord[to])
            else:
                if low[v] == Ord[v]:
                    while True:
                        u = visited.pop()
                        Ord[u] = N
                        ids[u] = NG[1]
                        if u == v:
                            break
                    NG[1] += 1
                low[bef] = min(low[bef], low[v])

    for i in range(N):
        if Ord[i] == -1:
            dfs(i)
    for i in range(N):
        ids[i] = NG[1] - 1 - ids[i]
    for i in range(n):
        if ids[2 * i] == ids[2 * i + 1]:
            return None
        answer[i] = ids[2 * i] < ids[2 * i + 1]
    return answer


def solve():
    n, q, m = map(int, input().split())
    clause = []

    def f(i, j):
        return i * (m + 1) + j

    for _ in range(q):
        query = list(map(int, input().split()))
        if query[0] == 1:
            i = query[1] - 1
            x = query[2]
            clause.append((f(i, x), False, f(i, x - 1), True))
        if query[0] == 2:
            i = query[1] - 1
            j = query[2] - 1
            x = query[3]
            for k in range(m + 1):
                if 0 <= x - k - 1 <= m:
                    clause.append((f(i, k), True, f(j, x - k - 1), True))
        if query[0] == 3:
            i = query[1] - 1
            j = query[2] - 1
            x = query[3]
            for k in range(m + 1):
                if 0 <= x - k - 1 <= m:
                    clause.append((f(i, k), False, f(j, x - k - 1), False))

    for i in range(n):
        clause.append((f(i, 0), False, f(i, 0), False))
        clause.append((f(i, m), True, f(i, m), True))
        for j in range(m):
            clause.append((f(i, j), False, f(i, j + 1), True))
        if i != 0:
            for j in range(1, m + 1):
                clause.append((f(i - 1, j), True, f(i, j), False))

    ans = two_sat(n * (m + 1), clause)
    if ans:
        ANS = [0] * n
        for i in range(n):
            for j in range(1, m + 1):
                if ans[f(i, j)]:
                    ANS[i] = j
                    break
        print(*ANS)
    else:
        print(-1)


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/