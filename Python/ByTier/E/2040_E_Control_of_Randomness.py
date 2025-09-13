# Contest 2040, Problem E: Control of Randomness
# URL: https://codeforces.com/contest/2040/problem/E

import sys

input = sys.stdin.readline


def solve():
    n, q = map(int, input().split())
    G = [[] for _ in range(n)]
    for _ in range(n - 1):
        a, b = map(int, input().split())
        a -= 1
        b -= 1
        G[a].append(b)
        G[b].append(a)
    P = [-1] * n
    Q = [0]
    for i in Q:
        for j in G[i]:
            if P[i] != j:
                Q.append(j)
                P[j] = i
    for _ in range(q):
        idx, p = map(int, input().split())
        idx -= 1
        switch = 0
        l = []
        ans = 0
        while idx != 0:
            if switch:
                l.append(len(G[idx]) - 1)
            switch ^= 1
            idx = P[idx]
            ans += 1
        l.sort()
        for _ in range(min(len(l), p)):
            l.pop()
        print(ans + sum(l) * 2)


for _ in range(int(input())):
    solve()
