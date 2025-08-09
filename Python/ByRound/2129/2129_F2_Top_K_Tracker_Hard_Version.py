# Contest 2129, Problem F2: Top-K Tracker (Hard Version)
# URL: https://codeforces.com/contest/2129/problem/F2

import random
import sys

input = lambda: sys.stdin.readline().strip()
flush = lambda: sys.stdout.flush()

N = 1010
Sv = [[] for _ in range(N)]
Sp = [[] for _ in range(N)]
prv = [[] for _ in range(N)]
prp = [[] for _ in range(N)]

def init():
    global n
    n = int(input())
    for i in range(N):
        Sv[i].clear()
        Sp[i].clear()
        prv[i].clear()
        prp[i].clear()

def ask(ty, v):
    print(f"{ty} {len(v)} {' '.join(map(str, v))}")
    flush()
    k = min(60, len(v)) if ty < 3 else min(300, len(v))
    res = list(map(int, input().split()))
    return res

def solve():
    cnt = 0
    cntr = 871
    p = [0] * (n + 4)

    for i in range(1, 30):
        cnt += 1
        Sv[cnt].append(i)
        cntr -= 1
        Sv[cntr].append(i)

    for i in range(1, 30):
        for j in range(i + 1, 30):
            cnt += 1
            Sv[cnt].extend([i, j])
            cntr -= 1
            Sv[cntr].extend([i, j])

    hd = 1
    for i in range(871, n):
        x, y, z = hd, hd + 1, hd + 2
        if x > 29: x -= 29
        if y > 29: y -= 29
        if z > 29: z -= 29
        Sv[i].extend([x, y, z])
        hd += 3

    for i in range(1, 30):
        v = []
        for j in range(1, n + 1):
            if i in Sv[j]:
                v.append(j)
        if not v:
            continue
        t = ask(2, v)
        for val in t:
            Sp[val].append(i)

    for i in range(1, n + 1):
        Sp[i].sort()
        Sv[i].sort()

    for i in range(1, n + 1):
        for j in range(871, n + 1):
            if Sp[i] == Sv[j]:
                p[i] = j

    for i in range(1, n + 1):
        if len(Sp[i]) == 1:
            prp[Sp[i][0]].append(i)
        elif len(Sp[i]) == 2:
            key = 30 * Sp[i][0] + Sp[i][1]
            prp[key].append(i)

    for i in range(1, n + 1):
        if len(Sv[i]) == 1:
            prv[Sv[i][0]].append(i)
        elif len(Sv[i]) == 2:
            key = 30 * Sv[i][0] + Sv[i][1]
            prv[key].append(i)

    for i in range(1, N):
        if len(prp[i]) >= 2 and random.randint(0, 1):
            prp[i][0], prp[i][1] = prp[i][1], prp[i][0]

    v = []
    for j in range(1, N):
        if not prp[j]:
            continue
        if len(prp[j]) == 1:
            p[prp[j][0]] = prv[j][0]
            prp[j].clear()
            prv[j].clear()
            continue
        v.append(prp[j][0])

    if v:
        t = ask(3, v)
        for j in range(1, N):
            if not prp[j] or not prv[j]:
                continue
            if not t:
                break
            if prv[j][1] == t[-1]:
                t.pop()
                p[prp[j][0]] = prv[j][1]
                p[prp[j][1]] = prv[j][0]
            else:
                p[prp[j][0]] = prv[j][0]
                p[prp[j][1]] = prv[j][1]
            prp[j].clear()
            prv[j].clear()

    print("! " + " ".join(str(p[i]) for i in range(1, n + 1)))
    flush()

def main():
    T = int(input())
    for _ in range(T):
        init()
        solve()

if __name__ == "__main__":
    main()
