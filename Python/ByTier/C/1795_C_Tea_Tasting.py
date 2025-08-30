# Contest 1795, Problem C: Tea Tasting
# URL: https://codeforces.com/contest/1795/problem/C

import bisect
import sys

input = sys.stdin.readline

for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    psa = [0]
    for x in b:
        psa.append(psa[-1] + x)
    offset = [0] * n
    r = [(i + 1) * b[i] for i in range(n)]
    for i in range(n):
        j = bisect.bisect_right(psa, a[i] + psa[i]) - 1
        if j < n:
            r[j] -= b[j]
            r[j] += a[i] + psa[i] - psa[j]
            offset[j] += 1
    acc = 0
    for i in range(n):
        r[i] -= b[i] * acc
        acc += offset[i]

    print(" ".join(map(str, r)))
