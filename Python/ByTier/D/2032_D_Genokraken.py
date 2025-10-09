# Contest 2032, Problem D: Genokraken
# URL: https://codeforces.com/contest/2032/problem/D

import sys, os

input = sys.stdin.buffer.readline

a, b = "?".encode(), "!".encode()


def f(x, y):
    os.write(1, b"%s %d %d\n" % (a, x, y))
    return int(input())


def g(x):
    os.write(1, b"%s %s\n" % (b, " ".join(map(str, x)).encode()))
    return


t = int(input())
for _ in range(t):
    n = int(input())
    u = n - 1
    for i in range(2, n - 1):
        if not f(1, i):
            u = i
            break
    p = [0] * n
    p[u] = 1
    x = [i for i in range(2, u + 1)]
    u += 1
    for v in x:
        if u >= n:
            break
        if not f(u, v):
            p[u] = v
            x.append(u)
            u += 1
    g(p[1:])
exit()
