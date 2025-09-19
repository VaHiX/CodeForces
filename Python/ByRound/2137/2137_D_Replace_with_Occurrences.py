# Contest 2137, Problem D: Replace with Occurrences
# URL: https://codeforces.com/contest/2137/problem/D

import sys

x = list(map(int, sys.stdin.read().split()))
y = iter(x)
z = next(y)
o = []
while z > 0:
    n = next(y)
    m = [next(y) for _ in range(n)]
    d = {}
    for i, j in enumerate(m):
        d.setdefault(j, []).append(i)
    f = 1
    a = [0] * n
    c = 0
    for k, v in d.items():
        if len(v) % k:
            f = 0
            break
        i = 0
        while i < len(v):
            c += 1
            for j in v[i : i + k]:
                a[j] = c
            i += k
    o.append("-1" if not f else " ".join(map(str, a)))
    z -= 1
print("\n".join(o))
