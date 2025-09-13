# Contest 1936, Problem A: Bitwise Operation Wizard
# URL: https://codeforces.com/contest/1936/problem/A

import sys, os

input = sys.stdin.buffer.readline


def f(a, b, c, d):
    os.write(1, b"%s %d %d %d %d\n" % (p, a, b, c, d))
    return input().rstrip().decode()


def g(a, b):
    os.write(1, b"%s %d %d\n" % (q, a, b))
    return


t = int(input())
p, q = "?".encode(), "!".encode()
for _ in range(t):
    n = int(input())
    x = 0
    for y in range(1, n):
        c = f(x, x, y, y)
        if c == "<":
            x = y
    y = x
    u = []
    for z in range(n):
        c = f(x, y, x, z)
        if c == "<":
            y = z
            u = [y]
        elif c == "=":
            u.append(z)
    y = u[0]
    for z in u:
        c = f(y, y, z, z)
        if c == ">":
            y = z
    g(x, y)
exit()
