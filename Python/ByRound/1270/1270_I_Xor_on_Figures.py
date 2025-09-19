# Contest 1270, Problem I: Xor on Figures
# URL: https://codeforces.com/contest/1270/problem/I

k = int(input())
dim = 1<<k
grid = [[[0]*dim for _ in range(dim)] for _ in range(2)]
for i in range(dim):
    grid[0][i] = list(map(int, input().split()))
t = int(input())
fig = []
for _ in range(t):
    x, y = map(int, input().split())
    fig.append((x-1, y-1))
for q in range(k):
    for i in range(dim):
        for j in range(dim):
            grid[1-q&1][i][j] = 0
            for p in fig:
                x = (i-p[0]) % dim
                y = (j-p[1]) % dim
                grid[1-q&1][i][j] ^= grid[q&1][x][y]
    for i in range(t):
        fig[i] = (fig[i][0]*2 % dim, fig[i][1]*2 % dim)
ans = 0
for i in range(dim):
    for j in range(dim):
        if grid[k&1][i][j]:
            ans += 1
print(ans)