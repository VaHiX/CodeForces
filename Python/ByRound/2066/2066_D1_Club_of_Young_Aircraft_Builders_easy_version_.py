# Contest 2066, Problem D1: Club of Young Aircraft Builders (easy version)
# URL: https://codeforces.com/contest/2066/problem/D1

import sys

input = sys.stdin.readline

mod = 10**9 + 7

FACT = [1]
for i in range(1, 2 * 10**5 + 1):
    FACT.append(FACT[-1] * i % mod)

FACT_INV = [pow(FACT[-1], mod - 2, mod)]
for i in range(2 * 10**5, 0, -1):
    FACT_INV.append(FACT_INV[-1] * i % mod)

FACT_INV.reverse()


def Combi(a, b):
    if 0 <= b <= a:
        return FACT[a] * FACT_INV[b] % mod * FACT_INV[a - b] % mod
    else:
        return 0


t = int(input())
for tests in range(t):
    n, c, m = map(int, input().split())
    A = list(map(int, input().split()))

    x = (n - 1) * c

    # print(x)

    print(Combi(x, m - c))
