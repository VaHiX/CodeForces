# Contest 2069, Problem C: Beautiful Sequence
# URL: https://codeforces.com/contest/2069/problem/C

from sys import stdin

R = stdin.readline
S = lambda: map(int, R().split())
P = print

X = 998244353
for _ in range(int(R())):
    n = int(R())
    d = [0, 0, 0]
    for x in S():
        if x == 1:
            d[0] += 1
        elif x == 2:
            d[1] = (2 * d[1] + d[0]) % X
        else:
            d[2] = (d[2] + d[1]) % X
    P(d[2])
