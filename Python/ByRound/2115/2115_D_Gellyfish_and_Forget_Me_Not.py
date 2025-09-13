# Contest 2115, Problem D: Gellyfish and Forget-Me-Not
# URL: https://codeforces.com/contest/2115/problem/D

import sys

input = sys.stdin.readline

from math import gcd

out = []

t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    c = input().strip()

    base = 0
    for i in range(n):
        base ^= a[i]
        b[i] ^= a[i]

    fixed = [0] * n
    for bt in range(60)[::-1]:
        mask = 1 << bt

        i = n - 1
        while i >= 0:
            if b[i] & mask == 0 or fixed[i]:
                i -= 1
                continue

            diff = b[i]
            fixed[i] = 1

            if c[i] == "1":
                base = max(base, base ^ diff)
            else:
                base = min(base, base ^ diff)

            break

        # print(bt, i, b)

        i -= 1
        while i >= 0:
            if b[i] & mask:
                b[i] ^= diff
            i -= 1

    out.append(base)

print("\n".join(map(str, out)))
