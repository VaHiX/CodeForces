# Contest 2034, Problem F1: Khayyam's Royal Decree (Easy Version)
# URL: https://codeforces.com/contest/2034/problem/F1

ans = []
MOD = 0x3B800001
N = 400_002
fact = [1]
for i in range(1, N):
    fact.append(fact[-1] * i % MOD)
anti = [0] * N
anti[-1] = pow(fact[-1], -1, MOD)
for i in range(N - 2, -1, -1):
    anti[i] = anti[i + 1] * (i + 1) % MOD


def cmb(n, k):
    if not 0 <= k <= n:
        return 0
    return fact[n] * anti[n - k] * anti[k] % MOD


for _ in range(int(input())):
    n, m, k = [int(t) for t in input().split()]

    pts = [[int(t) for t in input().split()] for _ in range(k)]
    pts.sort(key=lambda x: x[0] + x[1])

    v = [0] * k
    for i in range(k):
        a, b = pts[i]
        S = cmb(a + b, b)
        for j in range(i):
            c, d = pts[j]
            if c <= a and d <= b:
                S += cmb(a + b - c - d, a - c) * v[j]
        v[i] = S % MOD

    tot = 0
    for i in range(k):
        a, b = pts[i]
        tot += cmb(n - a + m - b, n - a) * v[i] * (2 * (n - a) + m - b)
    tot = tot * pow(cmb(n + m, m), -1, MOD) % MOD
    tot += 2 * n + m
    ans.append(tot % MOD)

for w in ans:
    print(w)
