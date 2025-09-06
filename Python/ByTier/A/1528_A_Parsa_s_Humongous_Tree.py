# Contest 1528, Problem A: Parsa's Humongous Tree
# URL: https://codeforces.com/contest/1528/problem/A

from sys import stdin,stdout
input = stdin.readline
# from math import gcd
# from collections import Counter
# from heapq import heapify,heappop,heappush


def Aniket_travel(u, p, d, dp0, dp1, l, r):
    for neighbor in d[u]:
        if neighbor != p:
            Aniket_travel(neighbor, u, d, dp0, dp1, l, r)
    dp0[p] += max(dp0[u] + abs(l[p] - l[u]), dp1[u] + abs(l[p] - r[u]))
    dp1[p] += max(dp0[u] + abs(r[p] - l[u]), dp1[u] + abs(r[p] - r[u]))
for _ in range(int(input())):
    n = int(input())
    l = [0] * (n + 1)
    r = l.copy()
    dp0 = l.copy()
    dp1 = l.copy()
    for i in range(n):
        x, y = map(int, input().split())
        l[i + 1] = x
        r[i + 1]=y
    d = [[] for i in range(n + 1)]
    for i in range(n - 1):
        u, v = map(int,input().split())
        d[u].append(v)
        d[v].append(u)
    Aniket_travel(1, 0, d, dp0, dp1, l, r)
    print(max(dp0[1], dp1[1]))
