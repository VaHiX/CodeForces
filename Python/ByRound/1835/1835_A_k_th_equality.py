# Contest 1835, Problem A: k-th equality
# URL: https://codeforces.com/contest/1835/problem/A

import sys

input = sys.stdin.readline


def solve():
    A, B, C, k = map(int, input().split())

    al = 10 ** (A - 1)
    ah = 10**A - 1
    bl = 10 ** (B - 1)
    bh = 10**B - 1
    cl = 10 ** (C - 1)
    ch = 10**C - 1

    if ch < al + bl or cl > ah + bh:
        return -1

    for a in range(al, ah + 1):
        low = max(cl - a, bl)
        high = min(ch - a, bh)
        x = max(0, high - low + 1)
        if k - x > 0:
            k -= x
        else:
            b = low + k - 1
            return f"{a} + {b} = {a + b}"

    return -1


T = int(input())
out = [solve() for _ in range(T)]
print("\n".join(map(str, out)))
