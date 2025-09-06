# Contest 2112, Problem E: Tree Colorings
# URL: https://codeforces.com/contest/2112/problem/E

import sys

data = sys.stdin.buffer.read().split()
t = int(data[0])
ms = list(map(int, data[1:]))
M = max(ms)
INF = M + 5
dpch = [INF] * (M + 1)
dp = [INF] * (M + 1)
dpch[1] = 0
for g in range(1, M + 1):
    if dpch[g] == INF:
        continue
    dp[g] = dpch[g] + 1
    a = g + 2
    cost = dp[g]
    lim = M // a
    for x in range(1, lim + 1):
        c = dpch[x] + cost
        m = x * a
        if c < dpch[m]:
            dpch[m] = c
out = []
for m in ms:
    ans = dp[m]
    out.append(str(ans if ans < INF else -1))
sys.stdout.write("\n".join(out))
