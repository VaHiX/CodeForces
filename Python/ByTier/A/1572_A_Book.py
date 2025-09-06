# Contest 1572, Problem A: Book
# URL: https://codeforces.com/contest/1572/problem/A

import sys

input = sys.stdin.readline

class graph(object):
    def __init__(self, n):
        self.arr = [[] for _ in range(n)]
        self.vertices = n

    def add(self, v, u):
        self.arr[v].append(u)
        #self.arr[u].append(v)

    def dfs(self):
        visited = [0] * self.vertices
        topsort = [0] * self.vertices
        stack = []

        k = self.vertices - 1
        for i in range(self.vertices):
            if not visited[i]:
                stack.append(i)

                while stack:
                    v = stack[-1]

                    if not visited[v]:
                        visited[v] = 1
                        for u in self.arr[v]:
                            if not visited[u]:
                                stack.append(u)
                            elif visited[u] == 1:
                                return -1
                    else:
                        if visited[v] == 1:
                            topsort[k] = v
                            k -= 1
                        visited[v] = 2
                        stack.pop()

        dp = [0] * self.vertices

        for v in topsort:
            for u in self.arr[v]:
                dp[u] = max(dp[u], dp[v] + int(u > v))

        return max(dp) + 1


def solve():
    n = int(input())
    g = graph(n)

    for i in range(n):
        arr = [int(v) for v in input().split()]
        for j in range(1, len(arr)):
            g.add(i, arr[j] - 1)

    print(g.dfs())


if __name__ == "__main__":
    t = 1
    t = int(input())
    while t > 0:
        solve()
        t -= 1