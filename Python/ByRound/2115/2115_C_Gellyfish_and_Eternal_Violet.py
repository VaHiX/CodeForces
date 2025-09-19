# Contest 2115, Problem C: Gellyfish and Eternal Violet
# URL: https://codeforces.com/contest/2115/problem/C

import math

logf = [0]
for i in range(1, 10000):
    logf.append(logf[-1] + math.log(i))


def lcmb(n, k):
    return logf[n] - logf[n - k] - logf[k]


baku = []
for _ in range(int(input())):
    n, m, p = [int(t) for t in input().split()]
    h = [int(t) for t in input().split()]
    if p == 100:
        if all(e == h[0] for e in h) and m >= h[0] - 1:
            baku.append(1)
        else:
            baku.append(0)
        continue
    if p == 0:
        if m >= sum(h) - n:
            baku.append(1)
        else:
            baku.append(0)
        continue
    p /= 100

    mh = min(h)
    extra = sum(h) - mh * n
    stair = (mh - 1) * n

    v = [0] * (stair + 1 + n)
    v[stair] = 1
    save = [v[: stair + 1 : n]]
    for _ in range(m - extra):
        for i in range(stair):
            v[i] = p * max(v[i], v[i + n]) + (1 - p) * max(v[i], v[i + 1])
        save.append(v[: stair + 1 : n])

    if extra == 0:
        baku.append(save[m][0])
        continue

    tot = 0
    for big in range(m - extra + 1):
        x = lcmb(extra + big - 1, extra - 1)
        x += math.log(1 - p) * extra
        x += math.log(p) * big
        tot += math.exp(x) * save[m - big - extra][min(mh - 1, big)]
    baku.append(tot)
print(*baku)
