# Contest 1866, Problem L: Lihmuf Balling
# URL: https://codeforces.com/contest/1866/problem/L

from math import gcd

N, M = map(int, input().split())
ans, bestK = 0, 1
for K in range(2, min(N, M) + 1):
    if N % K == 0:
        x = N // K
        cur = K * x * (x + 1) // 2
        if cur > ans:
            ans, bestK = cur, K
        continue
    elif gcd(N, K) > 1:
        continue

    cur = 0
    id, c = 1, K
    while id < N:
        ct = (N - c) // K
        sw = (1 + (id - c) // (K - 1)) if id >= c else 0
        if sw <= ct:
            cur += c * (ct - sw + 1) + K * (ct * (ct + 1) // 2 - sw * (sw - 1) // 2)
        id += ct + 1
        c = (c + (ct + 1) * K - 1) % N
        c += 1
    if cur > ans:
        ans, bestK = cur, K

print(bestK)
