# Contest 1830, Problem A: Copil Copac Draws Trees
# URL: https://codeforces.com/contest/1830/problem/A

from sys import stdin

input = lambda: stdin.readline()[:-1]


def solve():
    n = int(input())
    edge = [[] for i in range(n)]
    for i in range(n - 1):
        a, b = map(lambda x: int(x) - 1, input().split())
        edge[a].append((b, i))
        edge[b].append((a, i))
    dp = [0] * n
    ord = [-1] * n
    ord[0] = n
    todo = [0]
    while todo:
        v = todo.pop()
        for u, i in edge[v]:
            if ord[u] == -1:
                ord[u] = i
                if ord[v] > ord[u]:
                    dp[u] = dp[v] + 1
                else:
                    dp[u] = dp[v]
                todo.append(u)
    print(max(dp))


for _ in range(int(input())):
    solve()
