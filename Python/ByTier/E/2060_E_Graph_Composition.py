# Contest 2060, Problem E: Graph Composition
# URL: https://codeforces.com/contest/2060/problem/E

import sys

input = sys.stdin.readline


def find(p, x):
    stack = []
    while x != p[x]:
        stack.append(x)
        x = p[x]
    while stack:
        p[stack.pop()] = x
    return x


def union(p, a, b):
    a, b = find(p, a), find(p, b)
    if a < b:
        p[b] = a
    else:
        p[a] = b


t = int(input())
for _ in range(t):
    n, m1, m2 = map(int, input().split())
    p1 = [i for i in range(n)]
    p2 = [i for i in range(n)]
    cnt1, cnt2 = n, n
    edge1 = []
    for _ in range(m1):
        a, b = map(int, input().split())
        a -= 1
        b -= 1
        edge1.append((a, b))
    for _ in range(m2):
        a, b = map(int, input().split())
        a -= 1
        b -= 1
        if find(p2, a) != find(p2, b):
            union(p2, a, b)
            cnt2 -= 1
    ans = 0
    for i, j in edge1:
        if find(p2, i) != find(p2, j):
            ans += 1
        elif find(p1, i) != find(p1, j):
            union(p1, i, j)
            cnt1 -= 1
    print(ans + cnt1 - cnt2)
