# Contest 219, Problem E: Parking Lot
# URL: https://codeforces.com/contest/219/problem/E

import heapq
import sys, os, io

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def update(i, x, y):
    i ^= l1
    mi[i], ma[i] = x, y
    i >>= 1
    while i:
        mi[i] = min(mi[i << 1], mi[i << 1 ^ 1])
        ma[i] = max(ma[i << 1], ma[i << 1 ^ 1])
        i >>= 1
    return


def get_min(s, t):
    s, t = s ^ l1, t ^ l1
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
    s, t = s ^ l1, t ^ l1
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


def f(u, v):
    return u << 20 ^ v


n, m = map(int, input().split())
l1 = pow(2, (n + 2).bit_length())
l2 = 2 * l1
inf = pow(10, 9) + 1
mi, ma = [inf] * l2, [-inf] * l2
now, h = [0] * (1 << 20), []
ans = []
for _ in range(m):
    t, x = map(int, input().split())
    if t == 1:
        while h:
            d, u = (1 << 20) - (h[0] >> 20), h[0] & 0xFFFFF
            if min(u - get_max(0, u), get_min(u, l1 - 1) - u) == d:
                break
            heapq.heappop(h)
        if mi[1] == inf:
            u = 1
        now[x] = u
        l, r = get_max(0, u), get_min(u, l1 - 1)
        update(u, u, u)
        for v in [l, r]:
            w = min(max((u + v) // 2, 1), n)
            d = min(abs(u - w), abs(v - w))
            if d:
                heapq.heappush(h, f((1 << 20) - d, w))
        ans0 = u
        ans.append(ans0)
    else:
        update(now[x], inf, -inf)
        if mi[1] == inf:
            now[x] = 0
            continue
        u, v = get_max(0, now[x]), get_min(now[x], l1 - 1)
        w = min(max((u + v) // 2, 1), n)
        d = min(abs(u - w), abs(v - w))
        if d:
            heapq.heappush(h, f((1 << 20) - d, w))
        now[x] = 0
sys.stdout.write("\n".join(map(str, ans)))
