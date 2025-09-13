# Contest 2140, Problem C: Ultimate Value
# URL: https://codeforces.com/contest/2140/problem/C

import sys


def input():
    return sys.stdin.readline().strip()


def bmw():
    return map(int, sys.stdin.readline().strip().split())


for _ in range(int(input())):
    n = int(input())
    a = [0] + list(bmw())
    ans = 0
    for i in range(1, n + 1):
        if i % 2 == 1:
            ans += a[i]
        else:
            ans -= a[i]
    mao = (n + 1) // 2
    mie = n // 2
    temp = max(2 * (mao - 1) if mao > 1 else 0, 2 * (mie - 1) if mie > 1 else 0)

    negative = mao1 = mie1 = float("-inf")
    for i in range(1, n + 1):
        if i % 2 == 1:
            if mie1 != negative:
                temp = max(temp, i - 2 * a[i] + mie1)
            mao1 = max(mao1, -i - 2 * a[i])
        else:
            if mao1 != negative:
                temp = max(temp, i + 2 * a[i] + mao1)
            mie1 = max(mie1, -i + 2 * a[i])

    print(ans + temp)
