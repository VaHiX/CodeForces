# Contest 2118, Problem F: Shifts and Swaps
# URL: https://codeforces.com/contest/2118/problem/F

import random

MOD = -1 + (1 << 61)
baku = []
for _ in range(int(input())):
    n, m = [int(t) for t in input().split()]
    l1 = [int(t) - 1 for t in input().split()]
    l2 = [int(t) - 1 for t in input().split()]

    BASE = random.randint(1, MOD - 1)
    HASHES = [random.randint(1, MOD - 1) for _ in range(m)]

    def hash(a):
        h = [1] * n
        bins = [[] for _ in range(m)]
        for i in range(n):
            bins[a[i]].append(i)
        for i in range(n):
            bins[a[i]].append(i + n)

        for j in range(1, m):
            b1, b2 = bins[j - 1], bins[j]
            for z in range(len(b2) // 2):
                i = -1
                jump = 1 << 20
                while jump:
                    if i + jump < len(b1) and b1[i + jump] < b2[z]:
                        i += jump
                    jump //= 2
                i += 1

                p = 1
                acc = HASHES[j]
                while i < len(b1) and b1[i] < b2[z + 1]:
                    p += acc * h[b1[i] % n]
                    acc = acc * HASHES[j] % MOD
                    i += 1
                h[b2[z]] = p % MOD

        fin = [h[i] for i in bins[m - 1] if i < n]
        p = 0
        acc = 1
        for e in fin:
            p += e * acc
            acc = acc * BASE % MOD
        p %= MOD

        best = (p, 0)
        down = pow(BASE, -1, MOD)
        up = pow(BASE, len(fin) - 1, MOD)
        for i in range(len(fin)):
            best = min(best, (p, i))
            e = fin[i]
            p = (e * up + (p - e) * down) % MOD

        i = best[1]
        return fin[i:] + fin[:i]

    baku.append("YES" if hash(l1) == hash(l2) else "NO")
print(*baku)
