# Contest 2114, Problem F: Small Operations
# URL: https://codeforces.com/contest/2114/problem/F

import math, collections

for _ in range(int(input())):
    x, y, k = map(int, input().split())
    if k == 1:
        print(0 if x == y else -1)
        continue
    g = math.gcd(x, y)
    a, b = x // g, y // g
    p = True
    for n in [a, b]:
        if not p:
            break
        m, d = n, 2
        while d * d <= m:
            if m % d == 0:
                if d > k:
                    p = False
                    break
                while m % d == 0:
                    m //= d
            d += 1
        if m > 1 and m > k:
            p = False
    if not p:
        print(-1)
        continue
    s = 0
    for n in [a, b]:
        if n == 1:
            continue
        q = collections.deque([n])
        z = {n: 0}
        while q:
            u = q.popleft()
            c = z[u]
            if u == 1:
                s += c
                break
            i = 1
            while i * i <= u:
                if u % i == 0:
                    for o, w in [(u // i, i), (i, u // i)]:
                        if 1 < o <= k and w not in z:
                            z[w] = c + 1
                            q.append(w)
                i += 1
    print(s)
