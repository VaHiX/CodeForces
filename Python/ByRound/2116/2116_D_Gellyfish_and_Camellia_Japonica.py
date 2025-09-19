# Contest 2116, Problem D: Gellyfish and Camellia Japonica
# URL: https://codeforces.com/contest/2116/problem/D

import sys

input = sys.stdin.readline


class seg:
    def __init__(self, n):
        self.n = n
        self.sz = 1
        while self.sz < n:
            self.sz <<= 1
        self.d = [0] * (2 * self.sz)

    def b(self):
        for i in range(1, self.n + 1):
            self.d[self.sz + i - 1] = i
        for i in range(self.sz - 1, 0, -1):
            self.d[i] = 0

    def u(self, pos, v):
        i = self.sz + pos - 1
        self.d[i] = v
        i >>= 1
        while i > 0:
            self.d[i] = 0
            i >>= 1

    def qr(self, pos):
        return self.d[self.sz + pos - 1]


def solve():
    n, q = map(int, input().split())
    b = [0] + list(map(int, input().split()))
    tot = n + q
    l, r, root, low, ans = (
        [0] * (tot + 1),
        [0] * (tot + 1),
        [0] * (tot + 1),
        [0] * (tot + 1),
        [0] * (tot + 1),
    )
    st = seg(n)
    st.b()

    for i in range(1, q + 1):
        x, y, z = map(int, input().split())
        u = n + i
        l[u], r[u] = st.qr(x), st.qr(y)
        st.u(z, u)

    for i in range(1, n + 1):
        root[st.qr(i)] = 1

    for i in range(1, n + 1):
        v = st.qr(i)
        if low[v] == 0:
            low[v] = b[i]

    flag = True
    for u in range(tot, 0, -1):
        if u > n and low[u] > 0:
            if low[l[u]] < low[u]:
                if root[l[u]]:
                    flag = False
                    break
                low[l[u]] = low[u]
            if low[r[u]] < low[u]:
                if root[r[u]]:
                    flag = False
                    break
                low[r[u]] = low[u]

    if not flag:
        print(-1)
        return

    for u in range(1, tot + 1):
        if u <= n:
            ans[u] = low[u]
        else:
            c = min(ans[l[u]], ans[r[u]])
            if root[u]:
                if c != low[u]:
                    flag = False
                    break
                ans[u] = c
            else:
                ans[u] = c

    print(-1 if not flag else " ".join(map(str, ans[1 : n + 1])))


for _ in range(int(input())):
    solve()
