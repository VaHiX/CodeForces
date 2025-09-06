# Contest 1483, Problem A: Basic Diplomacy
# URL: https://codeforces.com/contest/1483/problem/A

import sys
input = lambda :sys.stdin.readline()[:-1]
ni = lambda :int(input())
na = lambda :list(map(int,input().split()))
yes = lambda :print("yes");Yes = lambda :print("Yes");YES = lambda : print("YES")
no = lambda :print("no");No = lambda :print("No");NO = lambda : print("NO")
#######################################################################
for _ in range(ni()):
    n, m = na()
    a = [0]*n
    ans = [-1]*m
    que = [na() for i in range(m)]
    for i in range(m):
        q = que[i]
        if q[0] == 1:
            ans[i] = q[1]
            a[q[1]-1] += 1
    for i in range(m):
        q = que[i]
        if q[0] > 1:
            x,y = q[1],q[2]
            if a[x-1] < (m+1)//2:
                a[x-1] += 1
                ans[i] = x
            else:
                a[y-1] += 1
                ans[i] = y
    f = 1
    for i in range(n):
        if a[i]  > (m+1)//2:
            f = 0
            break
    if f:
        YES()
        print(*ans)
    else:
        NO()
