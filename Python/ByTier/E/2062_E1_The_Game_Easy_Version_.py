# Contest 2062, Problem E1: The Game (Easy Version)
# URL: https://codeforces.com/contest/2062/problem/E1

import sys

le = sys.__stdin__.read().split("\n")[::-1]
af = []
for zo in range(int(le.pop())):
    n = int(le.pop())
    l = list(map(int, le.pop().split()))
    Depth = [0] * n
    pi = [0]
    ar = [[] for _ in range(n)]
    for _ in range(n - 1):
        a, b = map(int, le.pop().split())
        a -= 1
        b -= 1
        ar[a].append(b)
        ar[b].append(a)
    jump = [0] * n
    parent = [0] * n
    po = [[] for k in range(n)]
    for k, v in enumerate(l):
        po[v - 1].append(k)
    ma = max(l) - 1
    while pi:
        u = pi.pop()
        ju = jump[u]
        du = Depth[u]
        if ju == 0:
            fju = u
        elif 2 * Depth[ju] - du == Depth[jump[ju]]:
            fju = jump[ju]
        else:
            fju = u
        for v in ar[u]:
            if parent[u] != v:
                parent[v] = u
                pi.append(v)
                Depth[v] = du + 1
                jump[v] = fju
    la = ma
    bo = False
    for k in range(la - 1, -1, -1):
        if po[k]:
            te = None
            nte = None
            for u in po[k]:
                if te is None:
                    te = u
                else:
                    nu = u
                    mte = te
                    if Depth[te] > Depth[u]:
                        nu, te = te, nu
                    while Depth[nu] > Depth[te]:
                        nu = jump[nu] if Depth[jump[nu]] >= Depth[te] else parent[nu]
                    if te != nu:
                        te, nte = mte, u
                        break
                    else:
                        if Depth[u] > Depth[te]:
                            te = u
                        else:
                            te = mte
            for v in po[la]:
                if Depth[v] < Depth[te]:
                    af.append(te + 1)
                    bo = True
                    break
                while Depth[v] > Depth[te]:
                    v = jump[v] if Depth[jump[v]] >= Depth[te] else parent[v]
                if v != te:
                    af.append(te + 1)
                    bo = True
                    break
                if nte is not None:
                    af.append(nte + 1)
                    bo = True
                    break
            la = k
            if bo:
                break
    if not (bo):
        af.append(0)
print("\n".join(map(str, af)))
