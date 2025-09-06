# Contest 966, Problem A: Stairs and Elevators
# URL: https://codeforces.com/contest/966/problem/A

import sys
input = lambda :sys.stdin.readline()[:-1]
ni = lambda :int(input())
na = lambda :list(map(int,input().split()))
yes = lambda :print("yes");Yes = lambda :print("Yes");YES = lambda : print("YES")
no = lambda :print("no");No = lambda :print("No");NO = lambda : print("NO")
#######################################################################

n, m, cl, ce, v = na()
l = na()
e = na()
q = ni()

from bisect import bisect_left as bl

for _ in range(q):
    x1, y1, x2, y2 = na()
    ans = 10 ** 18
    if x1 == x2:
        print(abs(y1 - y2))
    else:
        Y = bl(l, y1)
        if Y < len(l):
            ans = min(ans, abs(y1 - l[Y]) + abs(y2 - l[Y]) + abs(x1 - x2))
        if Y > 0:
            ans = min(ans, abs(y1 - l[Y - 1]) + abs(y2 - l[Y - 1]) + abs(x1 - x2))
        Y = bl(e, y1)
        if Y < len(e):
            ans = min(ans, abs(y1 - e[Y]) + abs(y2 - e[Y]) + (abs(x1 - x2) - 1) // v + 1)
        if Y > 0:
            ans = min(ans, abs(y1 - e[Y - 1]) + abs(y2 - e[Y - 1]) + (abs(x1 - x2) - 1) // v + 1)
        print(ans)