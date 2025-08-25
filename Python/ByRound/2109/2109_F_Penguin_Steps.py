# Contest 2109, Problem F: Penguin Steps
# URL: https://codeforces.com/contest/2109/problem/F

import sys

input = sys.stdin.readline

out = []

inf = 10**9


class DistanceKeeper:
    def __init__(self, n):
        self.m = 1
        while self.m < n:
            self.m *= 2
        self.data = 2 * self.m * [inf]
        self.dist = n * [inf]
        self.__getitem__ = self.dist.__getitem__

    def __setitem__(self, ind, x):
        self.dist[ind] = x
        ind += self.m
        self.data[ind] = x
        ind >>= 1
        while ind:
            self.data[ind] = min(self.data[2 * ind], self.data[2 * ind + 1])
            ind >>= 1

    def __getitem__(self, ind):
        return self.dist[ind]

    def trav(self):
        while self.data[1] != inf:
            x = self.data[1]

            ind = 1
            while ind < self.m:
                ind = 2 * ind + (self.data[2 * ind] != x)
            ind -= self.m

            self[ind] = inf
            self.dist[ind] = x
            yield ind


def dijkstra(graph, start):
    inf = 10**9

    n = len(graph)

    D = DistanceKeeper(n)
    D[start] = 0

    for node in D.trav():
        for nei, weight in graph[node]:
            new_dist = max(D[node], weight)
            if new_dist < D[nei]:
                D[nei] = new_dist

    return D.dist


def dijkstra2(graph, start, si):
    inf = k + 1

    n = len(graph)

    D = DistanceKeeper(n)
    D[start] = 0

    for node in D.trav():
        if node == si:
            break

        for nei, weight in graph[node]:
            new_dist = D[node] + weight
            if new_dist < D[nei]:
                D[nei] = new_dist

    return D.dist


# source: adapted from https://github.com/cheran-senthil/PyRival/pull/55
# modified to fix bugs

import sys

input = sys.stdin.readline

dX = [0, 0, -1, 1]
dY = [-1, 1, 0, 0]

ddX = [0, 0, -1, 1, -1, 1, -1, 1]
ddY = [-1, 1, 0, 0, -1, -1, 1, 1]

t = int(input())
for _ in range(t):
    n, r, k = map(int, input().split())

    cb = []
    board = [list(map(int, input().split())) for _ in range(n)]

    for line in board:
        cb.extend(line)

    col = [input().strip() for _ in range(n)]
    cc = "".join(col)

    adj = [[] for _ in range(n * n)]
    for i in range(n):
        for j in range(n):
            for d in range(4):
                ii, jj = i + dX[d], j + dY[d]

                if 0 <= ii < n and 0 <= jj < n:
                    adj[n * i + j].append(
                        (n * ii + jj, max(board[i][j], board[ii][jj]))
                    )

    init = dijkstra(adj, r * n - 1)
    best = init[0]

    ty = [0] * n * n
    st = []
    for i in range(n):
        st.append(i)
    for i in range(r):
        st.append(n * (i + 1) - 1)
    for i in st:
        ty[i] = 1
    while st:
        u = st.pop()

        i = u // n
        j = u % n

        if board[i][j] <= best:
            continue

        for d in range(8):
            ii = i + ddX[d]
            jj = j + ddY[d]

            if 0 <= ii < n and 0 <= jj < n and ty[n * ii + jj] == 0:
                ty[n * ii + jj] = 1
                st.append(n * ii + jj)

    lo = init[n * (n - 1)] - 1  # blocked
    hi = lo + k + 1  # unblock

    rr = []
    zzz = [0] * (n * n)
    for i in range(n):
        rr.append(n * n - i - 1)
    for i in range(r - 1, n):
        rr.append(n * i + n - 1)
    for u in rr:
        zzz[u] = 1

    for i in range(n):
        zzz[i] |= 2
        zzz[n * i] |= 2
    for i in range(r):
        zzz[(n * (i + 1) - 1)] |= 2

    while hi - lo > 1:
        mid = (lo + hi) // 2

        bl = [0] * n * n
        st = []

        adj2 = [[] for _ in range(n * n + 2)]
        so = n * n
        si = so + 1

        for i in range(n):
            for j in range(n):
                u = n * i + j

                if cb[u] <= mid:
                    if cc[u] == "0":
                        continue

                    if ty[u] == 1 and mid >= best:
                        continue

                cost = max(0, mid + 1 - cb[u])

                if zzz[u] & 1:
                    adj2[so].append((u, 0))

                for d in range(8):
                    ii = i + ddX[d]
                    jj = j + ddY[d]

                    if 0 <= ii < n and 0 <= jj < n:
                        adj2[u].append((n * ii + jj, cost))

                if zzz[u] & 2:
                    adj2[u].append((si, cost))

        ddd = dijkstra2(adj2, so, si)
        if ddd[si] <= k:
            lo = mid
        else:
            hi = mid

    out.append(f"{best} {hi}")

print("\n".join(out))
