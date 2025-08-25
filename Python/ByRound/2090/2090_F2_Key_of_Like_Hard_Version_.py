# Contest 2090, Problem F2: Key of Like (Hard Version)
# URL: https://codeforces.com/contest/2090/problem/F2

import sys

MOD = 10**9 + 7
INV2 = 500000004
MAXN = 20000

inv = [0] * MAXN
inv[1] = 1
for i in range(2, MAXN):
    inv[i] = MOD - MOD // i * inv[MOD % i] % MOD


def readints():
    return list(map(int, sys.stdin.read().split()))


input_data = []


def read():
    global input_data
    if not input_data:
        input_data = readints()
    return input_data.pop(0)


def solve():
    T = read()
    for _ in range(T):
        init()


def init():
    n = read()
    l = read()
    k = read()

    f = [[[0] * n for _ in range(l + 1)] for _ in range(k + 1)]
    pre = [0] * (n + 1)
    p = [0] * n
    q = [0] * n

    for i in range(1, l + 1):
        s = 1
        a = i // n
        b = i % n
        for j in range(n):
            s += f[0][i - 1][j]
            if s >= MOD:
                s -= MOD
        s = a * s % MOD
        pre[0] = 0
        for j in range(n):
            pre[j + 1] = pre[j] + f[0][i - 1][j]
            if pre[j + 1] >= MOD:
                pre[j + 1] -= MOD
        pre[n] += 1
        if pre[n] >= MOD:
            pre[n] -= MOD

        for j in range(b):
            temp = pre[j] + pre[n] - pre[n - b + j]
            if temp >= MOD:
                temp -= MOD
            if temp < 0:
                temp += MOD
            f[0][i][j] = temp

        for j in range(b, n):
            temp = pre[j] - pre[j - b]
            if temp < 0:
                temp += MOD
            f[0][i][j] = temp

        for j in range(n):
            f[0][i][j] = (f[0][i][j] + s) * inv[i] % MOD

    for d in range(1, k + 1):
        for i in range(1, l + 1):
            s = 1
            a = i // n
            b = i % n
            for j in range(n):
                s += f[d][i - 1][j]
                if s >= MOD:
                    s -= MOD
            s = a * s % MOD

            pre[0] = 0
            for j in range(n):
                pre[j + 1] = pre[j] + f[d][i - 1][j]
                if pre[j + 1] >= MOD:
                    pre[j + 1] -= MOD
            pre[n] += 1
            if pre[n] >= MOD:
                pre[n] -= MOD

            for j in range(b):
                temp = pre[j] + pre[n] - pre[n - b + j]
                if temp >= MOD:
                    temp -= MOD
                if temp < 0:
                    temp += MOD
                p[j] = temp

            for j in range(b, n):
                temp = pre[j] - pre[j - b]
                if temp < 0:
                    temp += MOD
                p[j] = temp

            for j in range(n):
                add_term = d * f[d - 1][i][(j + n - i % n) % n] % MOD
                p[j] = (p[j] + s + add_term) * inv[i + d] % MOD

            s = 1
            a = (i + d) // n
            b = (i + d) % n
            for j in range(n):
                s += f[d][i - 1][j]
                if s >= MOD:
                    s -= MOD
            s = a * s % MOD

            pre[0] = 0
            for j in range(n):
                pre[j + 1] = pre[j] + f[d][i - 1][j]
                if pre[j + 1] >= MOD:
                    pre[j + 1] -= MOD
            pre[n] += 1
            if pre[n] >= MOD:
                pre[n] -= MOD

            for j in range(b):
                temp = pre[j] + pre[n] - pre[n - b + j]
                if temp >= MOD:
                    temp -= MOD
                if temp < 0:
                    temp += MOD
                q[j] = temp

            for j in range(b, n):
                temp = pre[j] - pre[j - b]
                if temp < 0:
                    temp += MOD
                q[j] = temp

            for j in range(n):
                q[j] = (q[j] + s) * inv[i + d] % MOD

            for j in range(n):
                num = (i - 1) * p[j] + (i + d - 1) * q[j]
                f[d][i][j] = num % MOD * inv[(i << 1) + d - 2] % MOD

    print(" ".join(str(f[k][l][i]) for i in range(n)))


solve()
