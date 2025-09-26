# Contest 2003, Problem D2: Turtle and a MEX Problem (Hard Version)
# URL: https://codeforces.com/contest/2003/problem/D2

import sys, os, io
input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

def f(u, v):
    return u << 20 ^ v

t = int(input())
ans = []
l = 2 * pow(10, 5) + 5
color, c = [0] * l, 1
for _ in range(t):
    n, m = map(int, input().split())
    ma, z = 0, [0] * n
    for j in range(n):
        a = list(map(int, input().split()))[1:]
        for i in a:
            if i < l:
                color[i] = c
        x, u, v = 0, 2, [0] * 2
        while color[x] == c or u:
            if color[x] ^ c:
                u -= 1
                v[u] = x
            x += 1
        z[j] = f(v[1], v[0])
        ma = max(ma, v[0])
        c += 1
    dp = [i for i in range(ma + 1)]
    cnt = [0] * (ma + 1)
    for i in sorted(z, reverse = True):
        j, k = i >> 20, i & 0xfffff
        dp[j] = max(dp[j], dp[k])
        cnt[j] += 1
    m0 = max(z) >> 20
    for i in range(ma + 1):
        if cnt[i] > 1:
            m0 = max(m0, dp[i])
    v = min(ma, m)
    ans0 = (m * (m + 1) - v * (v + 1)) >> 1
    for i in range(v + 1):
        ans0 += max(m0, dp[i])
    ans.append(ans0)

    
sys.stdout.write("\n".join(map(str, ans)))