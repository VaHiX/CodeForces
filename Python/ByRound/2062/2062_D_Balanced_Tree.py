# Contest 2062, Problem D: Balanced Tree
# URL: https://codeforces.com/contest/2062/problem/D

from sys import stdin

input = lambda: stdin.readline().rstrip()
from collections import deque


def solve():
    n = int(input())
    l, r = [None] * n, [None] * n
    for i in range(n):
        l[i], r[i] = map(int, input().split())
    if n == 1:
        return l[0]

    deg = [0] * n
    mix = [0] * n
    for _ in range(n - 1):
        u, v = map(int, input().split())
        u -= 1
        v -= 1
        deg[u] += 1
        deg[v] += 1
        mix[u] ^= v
        mix[v] ^= u

    h = deque(i for i, u in enumerate(deg) if u == 1)
    ans = 0
    for _ in range(n - 1):
        u = h.popleft()
        v = mix[u]
        if l[u] > r[v]:
            ans += l[u] - r[v]
            l[v] = r[v]
        elif l[u] > l[v]:
            l[v] = l[u]
        mix[v] ^= u
        deg[v] -= 1
        if deg[v] == 1:
            h.append(v)
    return ans + l[h[0]]


for _ in range(int(input())):
    print(solve())
