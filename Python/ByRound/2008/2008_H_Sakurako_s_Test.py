# Contest 2008, Problem H: Sakurako's Test
# URL: https://codeforces.com/contest/2008/problem/H

import sys
input = sys.stdin.readline
for _ in range(int(input())):
    n,q = map(int, input().split())
    A =list(map(int, input().split()))
    X = [0] * (n + 1)
    for i in A:
        X[i] += 1
    PRE = [0]
    for i in X:
        PRE.append(i+PRE[-1])
    SOL = [0] * (n+1)
    SOL[1] = 0
    for i in range(2,n+1):
        lo = -1
        hi = i - 1
        while lo + 1 < hi:
            mid = (lo+hi)//2
            SC = 0
            for j in range(0,n+1,i):
                SC += PRE[min(j+mid + 1,n+1)] - PRE[j]
            if SC >= (n + 2) // 2:
                hi = mid
            else:
                lo = mid
        SOL[i] = hi
    print(*[SOL[int(input())] for _ in range(q)])