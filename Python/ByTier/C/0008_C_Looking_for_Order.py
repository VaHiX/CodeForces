# Contest 8, Problem C: Looking for Order
# URL: https://codeforces.com/contest/8/problem/C

sx, sy = map(int, input().split())
n = int(input())
xs, ys = [], []
for _ in range(n):
    x, y = map(int, input().split())
    xs.append(x)
    ys.append(y)

dist = [[0 for _ in range(n)] for _ in range(n)]
for i in range(n):
    for j in range(n):
        dist[i][j] = (
            (sx - xs[i]) ** 2
            + (xs[i] - xs[j]) ** 2
            + (xs[j] - sx) ** 2
            + (sy - ys[i]) ** 2
            + (ys[i] - ys[j]) ** 2
            + (ys[j] - sy) ** 2
        )

dp = [2**45] * (1 << n)
par = [-1] * (1 << n)
dp[0] = 0
for mask in range(1 << n):
    if dp[mask] == 2**45:
        continue
    chosen = -1
    for j in range(n):
        if ~mask >> j & 1:
            if chosen == -1:
                chosen = j
            new_mask = mask | (1 << j) | (1 << chosen)
            if dp[new_mask] > dp[mask] + dist[chosen][j]:
                dp[new_mask] = dp[mask] + dist[chosen][j]
                par[new_mask] = (1 << j) | (1 << chosen)

ans = []
mask = (1 << n) - 1
while mask:
    tmp = par[mask]
    ans.append(0)
    while tmp:
        v = tmp & -tmp
        ans.append(v.bit_length())
        tmp ^= v
    mask ^= par[mask]
ans += [0]
print(dp[-1])
print(*ans[::-1])
