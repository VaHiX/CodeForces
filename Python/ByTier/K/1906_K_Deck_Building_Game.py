# Contest 1906, Problem K: Deck-Building Game
# URL: https://codeforces.com/contest/1906/problem/K

import sys

input = sys.stdin.readline

mod, l = 998244353, 131072
n, a = int(input()), [0] * l
for x in map(int, input().split()):
    a[x] += 2
a[0], x = n, 2
while x <= l:
    k = x >> 1
    i = 0
    while i < l:
        for j in range(k):
            u, v = a[i + j], a[i + j + k]
            a[i + j] = (u + v) % mod
            a[i + j + k] = (u - v + mod) % mod
        i += x
    x <<= 1
v = pow(4, mod - 2, mod)
for i in range(l):
    k = (3 * n - a[i] + mod) * v % mod
    a[i] = (mod - 1 if k & 1 else 1) * pow(3, n - k, mod) % mod
h = (mod + 1) // 2
x = 2
while x <= l:
    k = x >> 1
    i = 0
    while i < l:
        for j in range(k):
            u, v = a[i + j], a[i + j + k]
            a[i + j] = (u + v) * h % mod
            a[i + j + k] = (u - v + mod) * h % mod
        i += x
    x <<= 1
print(a[0])
