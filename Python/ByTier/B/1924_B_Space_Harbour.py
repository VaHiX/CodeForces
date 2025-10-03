# Contest 1924, Problem B: Space Harbour
# URL: https://codeforces.com/contest/1924/problem/B

import sys, os, io

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v):
    return u << 28 ^ v


def update(i, x):
    i += l1
    mi[i] = ma[i] = i - l1
    s[i] = x
    i >>= 1
    while i:
        mi[i] = min(mi[2 * i], mi[2 * i + 1])
        ma[i] = max(ma[2 * i], ma[2 * i + 1])
        s[i] = s[2 * i] + s[2 * i + 1]
        i >>= 1
    return


def get_min(s, t):
    s, t = s + l1, t + l1
    ans = inf
    while s <= t:
        if s & 1:
            ans = min(ans, mi[s])
            s += 1
        s >>= 1
        if not t & 1:
            ans = min(ans, mi[t])
            t -= 1
        t >>= 1
    return ans


def get_max(s, t):
    s, t = s + l1, t + l1
    ans = -inf
    while s <= t:
        if s & 1:
            ans = max(ans, ma[s])
            s += 1
        s >>= 1
        if not t & 1:
            ans = max(ans, ma[t])
            t -= 1
        t >>= 1
    return ans


def get_sum(l, r):
    l, r = l + l1, r + l1
    ans = 0
    while l <= r:
        if l & 1:
            ans += s[l]
            l += 1
        l >>= 1
        if not r & 1:
            ans += s[r]
            r -= 1
        r >>= 1
    return ans


n, m, q = map(int, input().split())
x = list(map(int, input().split()))
v = list(map(int, input().split()))
y = [f(i, j) for i, j in zip(x, v)]
y.sort()
for i in range(m):
    x[i], v[i] = y[i] >> 28, y[i] & 0xFFFFFFF
u = [0] * (n + 1)
u[1] = 1
for i in range(m - 1):
    u[x[i + 1]] = v[i]
l1 = pow(2, (n + 1).bit_length())
l2 = 2 * l1
inf = pow(10, 9) + 1
mi, ma = [inf] * l2, [-inf] * l2
for i in x:
    mi[i ^ l1] = ma[i ^ l1] = i
for i in range(l1 - 1, 0, -1):
    mi[i] = min(mi[2 * i], mi[2 * i + 1])
    ma[i] = max(ma[2 * i], ma[2 * i + 1])
s = [0] * l2
for i in range(1, m):
    c = (x[i] - x[i - 1]) * (x[i] - x[i - 1] - 1) // 2
    s[x[i] ^ l1] = c * v[i - 1]
for i in range(l1 - 1, 0, -1):
    s[i] = s[2 * i] + s[2 * i + 1]
ans = []
for _ in range(q):
    t, l, r = map(int, input().split())
    if t == 1:
        x0, v0 = l, r
        l0, r0 = get_max(0, x0 - 1), get_min(x0 + 1, l1 - 1)
        u[x0] = u[r0]
        u[r0] = v0
        c = (x0 - l0) * (x0 - l0 - 1) // 2
        update(x0, c * u[x0])
        c = (r0 - x0) * (r0 - x0 - 1) // 2
        i = r0 + l1
        s[i] = c * v0
        i >>= 1
        while i:
            s[i] = s[2 * i] + s[2 * i + 1]
            i >>= 1
    else:
        if l == r and u[l]:
            ans0 = 0
            ans.append(ans0)
            continue
        ans0 = 0
        if not u[l - 1]:
            l0 = get_min(l, l1 - 1)
            c = (l0 - l) * (l0 - l + 1) // 2
            ans0 += c * u[l0]
            l = l0 + 1
        if not u[r]:
            r0 = get_min(r, l1 - 1)
            c = (r0 - r) * (r0 - r - 1) // 2
            ans0 -= c * u[r0]
            r = r0
        ans0 += get_sum(l, r)
        ans.append(ans0)
sys.stdout.write("\n".join(map(str, ans)))
