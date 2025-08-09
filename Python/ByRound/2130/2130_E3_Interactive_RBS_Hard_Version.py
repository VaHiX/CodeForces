# Contest 2130, Problem E3: Interactive RBS (Hard Version)
# URL: https://codeforces.com/contest/2130/problem/E3

import sys

for _ in range(int(input())):
    n = int(input())
    print("?", n, " ".join(str(x) for x in range(1, n + 1)))
    sys.stdout.flush()
    if input() == "0":
        op, cl = n, 1
    else:
        lo, hi = 1, n
        while lo < hi:
            m = (lo + hi) // 2
            print("?", m, " ".join(str(x) for x in range(1, m + 1)))
            sys.stdout.flush()
            if int(input()) > 0: 
                hi = m
            else: 
                lo = m + 1
        op, cl = lo - 1, lo
    s = bytearray(n + 1)
    s[op] = ord('(')
    s[cl] = ord(')')
    i = 1
    while True:
        qb = []
        q = []
        v = 0
        bc = 0
        while True:
            a = q and [cl] or []
            while i <= n and s[i]: 
                i += 1
            if i > n: 
                break

            a += [op, cl] * ((1 << (v >> 1)) - 1)
            a += [i, cl]
            a += [op, cl] * ((1 << ((v + 1) >> 1)) - 1)
            if len(q) + len(a) > 1001: 
                break

            np = (1 << (v >> 1)) + (1 << ((v + 1) >> 1)) - 1
            bc += np * (np + 1) // 2
            qb.append(i)
            q += a
            v += 1
            i += 1

        if not q: 
            break
        print("?", len(q), " ".join(str(v) for v in q))
        sys.stdout.flush()
        k = bc - int(input())
        for v in qb:
            s[v] = ord(")") if (k & 1) else ord("(")
            k >>= 1

    print("!", s[1:].decode())
    sys.stdout.flush()
