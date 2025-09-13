# Contest 2140, Problem E2: Prime Gaming (Hard Version)
# URL: https://codeforces.com/contest/2140/problem/E2

# Copyright, (c), Afif Ali Saadman, 12 year old os developer, uses, c, cpp, and python.


import sys

MOD = 10**9 + 7
innit = lambda: sys.stdin.readline().rstrip("\r\n")

t = int(innit())

MAXN = 80
MAXP = 2 * MAXN

C = [[0] * (MAXN + 1) for _ in range(MAXN + 1)]
for i in range(MAXN + 1):
    C[i][0] = C[i][i] = 1
    for j in range(1, i):
        C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD

S2 = [[0] * (MAXP + 1) for _ in range(MAXP + 1)]
S2[0][0] = 1
for n_ in range(1, MAXP + 1):
    for k_ in range(1, n_ + 1):
        S2[n_][k_] = (S2[n_ - 1][k_ - 1] + k_ * S2[n_ - 1][k_]) % MOD

MAXR = MAXP + 1
inv = [0] * (MAXR + 1)
inv[1] = 1
for i in range(2, MAXR + 1):
    inv[i] = MOD - MOD // i * inv[MOD % i] % MOD

baku = []

for _ in range(t):
    n, m = map(int, innit().split())
    k_good = int(innit())
    good_in = list(map(int, innit().split()))
    good = [0] * (n + 1)
    for g in good_in:
        good[g] = 1

    if m == 1:
        baku.append("1")
        continue

    A = [[] for _ in range(n + 1)]
    for k in range(1, n + 1):
        Ak = []
        for i in range(1, k + 1):
            if good[i]:
                Ak.append(i)
        A[k] = Ak

    f_prev = [0, 1]

    for k in range(2, n + 1):
        size = 1 << k
        f_cur = [0] * size
        allowed = A[k]
        alice_turn = ((n - k) & 1) == 0

        if alice_turn:
            for mask in range(size):
                val = 0
                for i in allowed:
                    low = mask & ((1 << (i - 1)) - 1)
                    high = mask >> i
                    child = low | (high << (i - 1))
                    if f_prev[child]:
                        val = 1
                        break
                f_cur[mask] = val
        else:
            for mask in range(size):
                val = 1
                for i in allowed:
                    low = mask & ((1 << (i - 1)) - 1)
                    high = mask >> i
                    child = low | (high << (i - 1))
                    if not f_prev[child]:
                        val = 0
                        break
                f_cur[mask] = val

        f_prev = f_cur
    dp_k = [0] * (n + 1)
    if n == 1:

        dp_k[0] = 0 if f_prev[0] == 0 else 1
        dp_k[1] = 1 if f_prev[1] == 1 else 0
    else:
        for mask in range(1 << n):
            if f_prev[mask]:
                dp_k[mask.bit_count()] += 1

    max_r = 2 * n + 1
    fall = [1] * (max_r + 1)

    for r in range(1, max_r + 1):
        fall[r] = fall[r - 1] * (m - (r - 1)) % MOD

    P = [0] * (2 * n + 1)
    for p in range(0, 2 * n + 1):
        s = 0
        Sp = S2[p]
        for j in range(0, p + 1):

            s = (s + Sp[j] * (fall[j + 1] * inv[j + 1] % MOD)) % MOD
        P[p] = s

    powm = [1] * (n + 1)
    for e in range(1, n + 1):
        powm[e] = powm[e - 1] * m % MOD

    S_k = [0] * (n + 1)
    for k in range(0, n + 1):
        tdeg = n - k
        s = 0
        for j in range(0, k + 1):
            term = C[k][j] * powm[k - j] % MOD
            if j & 1:
                term = MOD - term
            s = (s + term * P[j + tdeg]) % MOD
        S_k[k] = s

    ans = 0
    for k in range(0, n + 1):
        if dp_k[k]:
            ans = (ans + dp_k[k] * S_k[k]) % MOD

    baku.append(str(ans))

print(*baku)
