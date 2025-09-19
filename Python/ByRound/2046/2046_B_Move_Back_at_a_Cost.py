# Contest 2046, Problem B: Move Back at a Cost
# URL: https://codeforces.com/contest/2046/problem/B

# zzzZZZ
import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n = int(input())
    A = list(map(int, input().split()))
    A.reverse()
    SUFMIN = [int(1e10)]
    for i in range(n):
        SUFMIN.append(min(SUFMIN[-1], A[i]))
    P = []
    N = []
    omi = int(1e10)
    for i in range(n - 1, -1, -1):
        if A[i] > SUFMIN[i] or A[i] > omi:
            omi = min(omi, A[i] + 1)
            P.append(A[i] + 1)
        else:
            N.append(A[i])
    P.sort()
    N += P
    print(*N)
