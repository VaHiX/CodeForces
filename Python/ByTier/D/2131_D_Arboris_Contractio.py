# Contest 2131, Problem D: Arboris Contractio
# URL: https://codeforces.com/contest/2131/problem/D

import sys

input = sys.stdin.readline

for _ in range(int(input())):
    N = int(input())
    Dic = [[] for _ in range(1 + N)]

    for _ in range(N - 1):
        a, b = map(int, input().split())

        Dic[a].append(b)
        Dic[b].append(a)

    V = [0] * (1 + N)

    for i in range(1 + N):
        if len(Dic[i]) == 1:
            V[Dic[i][0]] += 1

    print(sum(V) - max(V) if N > 2 else 0)
