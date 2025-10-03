# Contest 2041, Problem D: Drunken Maze
# URL: https://codeforces.com/contest/2041/problem/D

from collections import deque

N, M = map(int, input().split())
S = [input() for n in range(N)]
dn = [0, 1, 0, -1]
dm = [1, 0, -1, 0]


def idx(n, m, d, c):
    return ((n * M + m) * 4 + d) * 4 + c


inf = 1 << 30
dist = [inf] * N * M * 4 * 4
queue = deque([])
for n in range(N):
    for m in range(M):
        if S[n][m] == "S":
            dist[idx(n, m, 0, 0)] = 0
            queue.append((n, m, 0, 0))
while queue:
    n, m, i, c = queue.popleft()
    d = dist[idx(n, m, i, c)]
    for ii in range(4):
        if i == ii:
            cc = c + 1
        else:
            cc = 1
        if cc == 4:
            continue
        nn = n + dn[ii]
        mm = m + dm[ii]
        if 0 <= nn < N and 0 <= mm < M and S[nn][mm] != "#":
            dd = d + 1
            if dist[idx(nn, mm, ii, cc)] > dd:
                dist[idx(nn, mm, ii, cc)] = dd
                queue.append((nn, mm, ii, cc))
ans = inf
for n in range(N):
    for m in range(M):
        if S[n][m] == "T":
            for i in range(4):
                for c in range(4):
                    ans = min(ans, dist[idx(n, m, i, c)])
if ans == inf:
    ans = -1
print(ans)
