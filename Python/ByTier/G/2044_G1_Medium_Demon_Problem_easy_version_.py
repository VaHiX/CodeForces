# Contest 2044, Problem G1: Medium Demon Problem (easy version)
# URL: https://codeforces.com/contest/2044/problem/G1

import sys

input = sys.stdin.readline

t = int(input())
for tests in range(t):
    n = int(input())
    A = list(map(int, input().split()))

    for i in range(n):
        A[i] -= 1

    DEG = [0] * n
    for a in A:
        DEG[a] += 1

    Q = []
    for i in range(n):
        if DEG[i] == 0:
            Q.append(i)

    ANS = 0

    while Q:
        ANS += 1
        NQ = []
        for q in Q:
            DEG[A[q]] -= 1
            if DEG[A[q]] == 0:
                NQ.append(A[q])
        Q = NQ

    print(ANS + 2)
