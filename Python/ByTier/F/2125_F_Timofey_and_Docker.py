# Contest 2125, Problem F: Timofey and Docker
# URL: https://codeforces.com/contest/2125/problem/F

import sys

input = sys.stdin.readline
baku = []
for _ in range(int(input())):
    s = input().rstrip()
    n = int(input())
    intvs = [[int(t) for t in input().split()] for _ in range(n)]

    if len(s) < 6:
        baku.append(0)
        continue
    v = [0] * (len(s) - 5)
    for i in range(len(s) - 5):
        t = s[i : i + 6]
        v[i] = sum(c != d for c, d in zip(t, "docker"))

    BIG = 1 << 63

    def solve(bonus):
        dp = [BIG] * 6
        dp[0] = 0
        for i in range(len(v)):
            dp[(i + 1) % 6] = min(dp[(i + 1) % 6], dp[i % 6])
            dp[i % 6] += +v[i] - bonus
        return min(dp)

    def want(x):
        z = -1
        jump = 1 << 20
        while jump:
            if solve(z + jump - 1) - solve(z + jump) <= x:
                z += jump
            jump //= 2
        return solve(z) + x * z

    base = v.count(0)

    events = []
    for l, r in intvs:
        events.append(2 * l + 1)
        events.append(2 * (r + 1))
    cur = 0
    mintvs = []
    last = 0
    for ev in sorted(events):
        x = ev // 2
        if last < x:
            mintvs.append((last, x, cur))
        cur += 1 if ev & 1 else -1
        last = x
    # print(mintvs)

    best = 0
    for l, r, d in mintvs:
        if l > len(s) // 6:
            continue
        best = max(best, d)
    cost = BIG
    top = -1
    for l, r, d in mintvs:
        if l > len(s) // 6:
            continue
        if d < best:
            continue
        if l <= base < r:
            cost = 0
            break
        if r <= base:
            cost = min(cost, base - r + 1)
            continue
        top = l
        break
    if top > -1:
        cost = min(cost, want(top))
    baku.append(cost)
print(*baku)
