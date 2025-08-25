# Contest 2090, Problem B: Pushing Balls
# URL: https://codeforces.com/contest/2090/problem/B

from sys import stdin

input = lambda: stdin.buffer.readline().decode().strip()


for _ in range(int(input())):
    n, m = map(int, input().split())
    g = [list(map(int, input())) for _ in range(n)]
    ans = "YES"

    for i in range(1, n):
        for j in range(1, m):
            if g[i][j]:
                if any(g[i][k] == 0 for k in range(j)) and any(
                    g[k][j] == 0 for k in range(i)
                ):
                    ans = "NO"

    print(ans)
