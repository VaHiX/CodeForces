# Contest 2084, Problem E: Blossom
# URL: https://codeforces.com/contest/2084/problem/E

MOD = 10**9 + 7


def modmul(x, y, c=0):
    return (x * y + c) % MOD


mod_mul = modmul


def inv(x):
    return pow(x, MOD - 2, MOD)


MAX = 10**4 * 3

fact = [1]
for i in range(1, MAX):
    fact.append(modmul(i, fact[i - 1]))

invfact = [1] * (MAX)
invfact[MAX - 1] = inv(fact[MAX - 1])
for i in range(MAX - 2, -1, -1):
    invfact[i] = modmul(i + 1, invfact[i + 1])


def comb(x, y):
    if 0 <= y <= x:
        return modmul(fact[x], modmul(invfact[y], invfact[x - y]))
    return 0


def perm(x, y):
    return modmul(fact[x], invfact[x - y])


def invcomb(x, y):
    return modmul(invfact[x], modmul(fact[y], fact[x - y]))


def invs(x):
    return modmul(fact[x - 1], invfact[x])


# Source: own (dnialh)

import sys

input = sys.stdin.readline

t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    z = a.count(-1)

    ct = [0] * (n + 1)
    for i in range(n):
        curr = 0
        for j in range(i, n):
            if a[j] == -1:
                curr += 1
            ct[curr] += 1

    l = n + 1
    r = -1

    out = 0
    miss = 0

    ctneg = 0

    for i in range(n):
        if i in a:
            if r == -1:
                l = r = a.index(i)

                ct = [0] * (n + 1)

                xx = 0
                for i in range(l, -1, -1):
                    if a[i] == -1:
                        xx += 1
                    curr = xx
                    for j in range(r, n):
                        if a[j] == -1:
                            curr += 1
                        ct[curr] += 1
                        # print(i, j)
            else:
                jj = a.index(i)

                while l > jj:
                    if a[l] == -1:
                        ctneg += 1

                    curr = ctneg
                    for j in range(r, n):
                        if a[j] == -1:
                            curr += 1
                        ct[curr] -= 1

                    l -= 1

                while r < jj:
                    if a[r] == -1:
                        ctneg += 1

                    curr = ctneg
                    for j in range(l, -1, -1):
                        if a[j] == -1:
                            curr += 1
                        ct[curr] -= 1

                    r += 1
            # print(l, r, ct)
        else:
            miss += 1

        # print(l, r, ct)

        """
        if r == -1:
            for k in range(i + 1, z + 1):
                #ut = modmul(modmul(ct[k], comb(k, i + 1)), comb(z, i + 1), c = out)
                ex = modmul(modmul(fact[k], invfact[k - i - 1]), fact[z - i - 1])
                out += modmul(ct[k], ex)

                #print(i, k, ex)
            out %= MOD
            continue

        exl = 0
        exr = 0

        curr = a[:l].count(-1)
        for x in range(l, -1, -1):
            if a[x] == -1:
                curr -= 1
            exl += modmul(comb(z - curr, miss), invcomb(z, miss))
        assert curr == 0

        curr = a[r:].count(-1)
        for x in range(r, n):
            if a[x] == -1:
                curr -= 1
            exr += modmul(comb(z - curr, miss), invcomb(z, miss))
        assert curr == 0
            
        exl %= MOD
        exr %= MOD

        print(exl, exr)
        out += modmul(modmul(exl, exr), fact[z])
        out %= MOD
        """

        for k in range(miss, z + 1):
            ex = modmul(modmul(fact[k], invfact[k - miss]), fact[z - miss])
            out += modmul(ct[k], ex)
            # print(i, k, ex)
        out %= MOD

    print(out)
