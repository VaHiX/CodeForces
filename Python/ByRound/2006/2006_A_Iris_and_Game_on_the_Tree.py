# Contest 2006, Problem A: Iris and Game on the Tree
# URL: https://codeforces.com/contest/2006/problem/A


def solve():
    n = int(input())
    deg = [0] * n
    for i in range(n - 1):
        x, y = map(int, input().split())
        deg[x - 1] += 1
        deg[y - 1] += 1
    c0 = c1 = c = 0
    s = input()
    for i in range(1, n):
        if deg[i] == 1:
            if s[i] == "0":
                c0 += 1
            elif s[i] == "1":
                c1 += 1
            else:
                c += 1
    if s[0] == "0":
        return c1 + (c + 1) // 2
    elif s[0] == "1":
        return c0 + (c + 1) // 2
    elif c0 != c1:
        return max(c0, c1) + c // 2
    else:
        c2 = 0
        for i in range(1, n):
            if deg[i] != 1 and s[i] == "?":
                c2 ^= 1
        return c0 + (c + c2) // 2


import sys

input = lambda: sys.stdin.readline().rstrip()
t = int(input())
for i in range(t):
    print(solve())
