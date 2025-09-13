# Contest 1109, Problem A: Sasha and a Bit of Relax
# URL: https://codeforces.com/contest/1109/problem/A

import sys
import math

input = sys.stdin.readline


def tt():
    sys.stdout.flush()


def fg():
    return int(input())


def fgh():
    return [int(xx) for xx in input().split()]


def p(ii):
    ans = 0
    while ii:
        ans += R[j][ii]
        ii -= F[ii]
    return ans


def pl(ii, x):
    while ii <= n:
        R[j][ii] += x
        ii += F[ii]


"""M = 998244353 + 10 ** 9 + 7
M1 = 10 ** 15 + 7
M2 = 655360001
d = [11, 15, 7, 13751, 13757, 13759, 13763, 13781, 29927, 29959, 29983, 29989, 2333, 2339, 2341, 2347, 2351, 9931, 9941, 9949, 9967, 9973]
F = []
for i in range(4 * 10 ** 5 + 3):
    F.append(i & (-i))
L = len(d)
n, q = fgh()
a = fgh()
for i in range(n):
    a[i] = (a[i] * M) % M1
R = [[0] * (n + 1) for i in range(L)]
for j in range(L):
    pr = [0]
    for i in range(n):
        pr.append(pr[-1] + (a[i] * d[j]) % M2)
    for i in range(1, n + 1):
        R[j][i] = pr[i] - pr[i - F[i]]
for _ in range(q):
    t = fgh()
    if t[0] == 2:
        l, r, k = t[1], t[2], t[3]
        l -= 1
        #print(*R)
        for j in range(L):
            q = p(r) - p(l)
            if q % k:
                print('No')
                break
        else:
            print('Yes')
    else:
        i, x = t[1], t[2]
        x = (x * M) % M1
        i -= 1
        for j in range(L):
            de = (x * d[j]) % M2 - (a[i] * d[j]) % M2
            pl(i + 1, de)
        #print(*R)
        a[i] = x"""
n = fg()
a = fgh()
l0 = {}
l1 = {}
ans = 0
pr = [0]
for i in range(n):
    pr.append(pr[-1] ^ a[i])
for i in range(n + 1):
    if i % 2:
        if pr[i] in l0:
            ans += l0[pr[i]]
            l0[pr[i]] += 1
        else:
            l0[pr[i]] = 1
    else:
        if pr[i] in l1:
            ans += l1[pr[i]]
            l1[pr[i]] += 1
        else:
            l1[pr[i]] = 1
print(ans)
