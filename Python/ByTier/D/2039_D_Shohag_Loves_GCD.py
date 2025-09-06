# Contest 2039, Problem D: Shohag Loves GCD
# URL: https://codeforces.com/contest/2039/problem/D

import sys
input = sys.stdin.readline

MX = 10 ** 5 + 10
sieve = [0] * MX
ct = [0] * 2

for i in range(2, MX):
    if sieve[i]:
        continue

    for j in range(i, MX, i):
        sieve[j] = i

for i in range(2, MX):
    ct.append(ct[i // sieve[i]] + 1)

out = []
t = int(input())
for _ in range(t):
    n, m = map(int, input().split())
    s = list(map(int, input().split()))

    if (1 << m) <= n:
        out.append('-1')
        continue

    res = []
    for i in range(1, n + 1):
        res.append(s[~ct[i]])

    out.append(' '.join(map(str, res)))

print('\n'.join(map(str, out)))
