# Contest 2063, Problem C: Remove Exactly Two
# URL: https://codeforces.com/contest/2063/problem/C

import sys

input = sys.stdin.readline

for _ in range(int(input())):
    n = int(input())
    indegree = [0] * (n + 1)
    graph = [[] for _ in range(n + 1)]
    for _ in range(n - 1):
        u, v = map(int, input().split())
        indegree[u] += 1
        indegree[v] += 1
        graph[u].append(v)
        graph[v].append(u)

    x = indegree.index(max(indegree))
    result = indegree[x]
    c = 0
    for nx in graph[x]:
        if indegree[nx] == indegree[x]:
            c += 1
        indegree[nx] -= 1
    if c >= 2:
        result = indegree[x] * 2 - 1
    else:
        indegree[x] = 0
        x = indegree.index(max(indegree))
        result += indegree[x] - 1
    print(result)
