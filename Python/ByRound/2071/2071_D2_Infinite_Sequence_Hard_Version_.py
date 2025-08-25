# Contest 2071, Problem D2: Infinite Sequence (Hard Version)
# URL: https://codeforces.com/contest/2071/problem/D2

import sys
from operator import xor
from functools import reduce
from math import gcd, inf, atan2, pi
from collections import deque, defaultdict

input = sys.stdin.readline

rn = lambda: int(input())
rs = lambda: input().strip()
rl = lambda: list(map(int, input().split()))


def solve():
    (_n, l, r), _a = rl(), [0] + rl()
    n, a = _n | 1, _a if _n & 1 else list(_a) + [reduce(xor, _a[: (_n + 1) // 2 + 1])]

    pre_xor = [0] * (n + 1)
    for i in range(1, n + 1):
        pre_xor[i] = pre_xor[i - 1] ^ a[i]
    rev = pre_xor[n]

    def _calc(m):
        k = m // 2
        return (
            a[m]
            if m <= n
            else (
                reduce(xor, a[: k + 1])
                if k <= n
                else reduce(xor, a)
                ^ (_calc(n + 1) if not n & 1 else 0)
                ^ (0 if k & 1 else _calc(k))
            )
        )

    def calc(m):
        if not (m & 1):
            return calc(m + 1) - _calc(m + 1)
        f = [
            max(0, ((m // 2 - (1 << i)) // (1 << (i + 1)) - n // 2)) << 1
            for i in range(0, 61, 2)
        ]
        z = [(i, (m // i).bit_length() - 1) for i in range(n // 2 + 1, n + 1)]

        res = (
            a[: m + 1].count(1)
            if m <= n
            else (
                sum([v << 1 for (i, v) in z if pre_xor[i]]) + a.count(1)
                if not rev
                else a.count(1) + sum(f) + sum([(v + pre_xor[i]) & -2 for (i, v) in z])
            )
        )
        return res

    print(calc(r) - calc(l - 1))


[solve() for _ in range(rn())]
