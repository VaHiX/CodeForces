# Contest 1039, Problem A: Timetable
# URL: https://codeforces.com/contest/1039/problem/A

import sys
input = lambda :sys.stdin.readline()[:-1]
ni = lambda :int(input())
na = lambda :list(map(int,input().split()))
yes = lambda :print("yes");Yes = lambda :print("Yes");YES = lambda : print("YES")
no = lambda :print("no");No = lambda :print("No");NO = lambda : print("NO")
#######################################################################


n, t = na()
a = na()
x = na()

S = [0] * (1 + n)
for i in range(n):
    S[x[i]] -= 1
    S[i+1] += 1


for i in range(n):
    S[i+1] += S[i]

from bisect import bisect_left, bisect_right
if all(x >= 0 for x in S) and all(x[i] <= x[i+1] for i in range(n-1)):
    
    b = [-1] * n
    FLAG = 1
    for i in range(n-1, -1, -1):
        if i > 0 and x[i-1] == x[i] and (i == n-1 or x[i] < x[i+1]):
            if x[i] < n and a[x[i]] - a[x[i]-1] == 1:
                FLAG = 0
            b[i] = a[x[i]-1] + 1
        elif i < n-1 and x[i] == x[i+1]:
            b[i] = b[i+1] - 1
        else:
            b[i] = a[x[i] - 1]
    if FLAG and all(b[i] < b[i+1] for i in range(n-1)):
        Yes()
        print(*[x + t for x in b])
    else:
        No()
else:
    No()