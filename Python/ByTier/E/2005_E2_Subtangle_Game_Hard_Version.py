# Contest 2005, Problem E2: Subtangle Game (Hard Version)
# URL: https://codeforces.com/contest/2005/problem/E2

import sys, os, io
input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

def f(u, v):
    return u << 12 ^ v

t = int(input())
ans = []
for _ in range(t):
    l, n, m = map(int, input().split())
    a = list(map(int, input().split()))
    color, c = [-1] * (n * m + 1), 0
    for i in a:
        if color[i] == -1:
            color[i], c = c, c + 1
    b = [-1] * (c << 12)
    for i in range(n):
        b0 = input().rstrip()
        j, x = 0, 0
        for c in b0:
            if not c & 16:
                if color[x] ^ -1 and n <= m:
                    b[f(color[x], i)] = j
                elif color[x] ^ -1:
                    b[f(color[x], j)] = i
                j, x = j + 1, 0
            else:
                x = 10 * x + (c & 15)
        if color[x] ^ -1 and n <= m:
            b[f(color[x], i)] = j
        elif color[x] ^ -1:
            b[f(color[x], j)] = i
    if not n <= m:
        n, m = m, n
    dp = [-1] * (n + 1)
    dp0 = [-1] * (n + 1)
    for i in a[::-1]:
        c = color[i]
        for j in range(n - 1, -1, -1):
            x = b[f(c, j)]
            dp0[j] = dp0[j + 1] if not dp[j + 1] <= x else max(dp0[j + 1], x)
        dp, dp0 = dp0, dp
    ans0 = "N" if not dp[0] ^ -1 else "T"
    ans.append(ans0)
sys.stdout.write("\n".join(ans))