# Contest 2112, Problem D: Reachability and Tree
# URL: https://codeforces.com/contest/2112/problem/D

import sys

le = sys.__stdin__.read().split("\n")[::-1]
af = []
for _ in range(int(le.pop())):
    n = int(le.pop())
    d = [0] * n
    ar = [[] for _ in range(n)]
    Bo = [True] * n
    nv = [True] * n
    for _ in range(n - 1):
        u, v = list(map(int, le.pop().split()))
        u -= 1
        v -= 1
        d[u] += 1
        d[v] += 1
        ar[u].append(v)
        ar[v].append(u)
    if 2 in d:
        af.append("YES")
        i = d.index(2)
        pi = [0 if i != 0 else 1]
        while pi:
            u = pi.pop()
            nv[u] = False
            if u == i:
                Bo[i] = not (Bo[i])
            for v in ar[u]:
                if nv[v]:
                    pi.append(v)
                    x, y = u + 1, v + 1
                    if Bo[u]:
                        x, y = y, x
                    Bo[v] = not (Bo[u])
                    af.append(str(x) + " " + str(y))
    else:
        af.append("NO")

print("\n".join(map(str, af)))
