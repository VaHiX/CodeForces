# Contest 2055, Problem E: Haystacks
# URL: https://codeforces.com/contest/2055/problem/E

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n = int(input())
    tas = 0
    thl = 0
    td = 0
    pd = []
    nd = []
    for _ in range(n):
        a, b = map(int, input().split())
        tas += a
        thl += b
        if b > a:
            pd.append((a, b))
        else:
            nd.append((b, a))
    pd.sort()
    nd.sort()
    mrd = 0
    ch = 0
    for a, b in nd:
        mrd = min(mrd, ch - a)
        ch += b - a
    lha = []
    ctd = 0
    for a, b in pd:
        ctd += b - a
        lha.append(ctd - b)
    hb = []
    cm = 0
    for i in lha:
        cm = min(cm, i)
        hb.append(cm)
    ha = []
    cm = 0
    for i in lha[::-1]:
        cm = min(cm, i)
        ha.append(cm)

    if len(nd) == 0 or nd[0][0] > thl - tas:
        nesi = None
        bap = -float("inf")
        for i in range(len(pd)):
            if pd[i][1] <= thl - tas:
                cp = min(
                    hb[i - 1] if i > 0 else 0,
                    ha[-i - 2] - (pd[i][1] - pd[i][0]) if i < len(pd) - 1 else 0,
                    mrd + thl - tas - pd[i][1] + pd[i][0],
                )
                if cp > bap:
                    nesi = i
                    bap = cp
        if nesi == None:
            print(-1)
        else:
            print(tas - bap)
    else:
        bap = min(mrd + thl - tas, hb[-1])
        print(tas - bap)
