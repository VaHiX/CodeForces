# Contest 2116, Problem B: Gellyfish and Baby's Breath
# URL: https://codeforces.com/contest/2116/problem/B

import sys

input = sys.stdin.readline
mod = 998244353
p = [1]
for j in range(10**5):
    p.append((p[-1] << 1) % mod)
for i in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    m1, m2 = (-1, -1), (-1, -1)
    out = []
    for j in range(n):
        m1 = max(m1, (a[j], j))
        m2 = max(m2, (b[j], j))
        if m1[0] > m2[0]:
            out.append((p[m1[0]] + p[b[j - m1[1]]]) % mod)
        elif m2[0] > m1[0]:
            out.append((p[m2[0]] + p[a[j - m2[1]]]) % mod)
        else:
            out.append((p[m1[0]] + p[max(a[j - m2[1]], b[j - m1[1]])]) % mod)
    print(*out)
