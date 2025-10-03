# Contest 2032, Problem F: Peanuts
# URL: https://codeforces.com/contest/2032/problem/F

MOD = 0x3B800001
HALF = pow(2, -1, MOD)
for _ in range(int(input())):
    n = int(input())
    a = [int(t) for t in input().split()]

    i = 0
    while i < n and a[i] == 1:
        i += 1

    if i == n:
        if i & 1:
            print(pow(2, n - 1, MOD))
        else:
            print(0)
        continue

    X = 0
    v = [0, 0]
    tot = 1
    bp = pow(2, n - 2 - i, MOD)
    for k in range(i, n):
        X ^= a[k]
        if k < n - 1:
            tot = 2 * tot % MOD
        if X < 2:
            if k == n - 1:
                v[X] += 1
            else:
                v[X] += bp  # v[X] += 1<<(max(0,n-2-k))
        bp = bp * HALF % MOD

    S = 0
    w = 1
    for t in range(i + 1):
        # w = 1<<(max(0,t-1))
        if t % 2 == 0:
            if (i - t) % 2 == 0:
                S += w * (tot - v[0])
            else:
                S += w * (tot - v[1])
        else:
            if (i - t) % 2 == 0:
                S += w * v[0]
            else:
                S += w * v[1]
        if t:
            w = w * 2 % MOD

    print(S % MOD)
