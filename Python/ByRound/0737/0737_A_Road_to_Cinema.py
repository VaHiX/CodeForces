# Contest 737, Problem A: Road to Cinema
# URL: https://codeforces.com/contest/737/problem/A

import sys
input = lambda :sys.stdin.readline()[:-1]
ni = lambda :int(input())
na = lambda :list(map(int,input().split()))
yes = lambda :print("yes");Yes = lambda :print("Yes");YES = lambda : print("YES")
no = lambda :print("no");No = lambda :print("No");NO = lambda : print("NO")
#######################################################################


n,k,s, t = na()
cv = [na() for _ in range(n)]
cv = sorted(cv, key = lambda x: x[1])
#print(cv)
z = []
for i in range(n):
    #print(z)
    if len(z) == 0:
        z.append(cv[i])
    else:
        while z and z[-1][0] >= cv[i][0]:
            z.pop()
        z.append(cv[i])

g = [0] + sorted(na()) + [s]

d = 0

ans = 10 ** 18

def check(v):
    res = 0
    for j in range(k+1):
        D = g[j+1] - g[j]
        if D > v:
            return False
        if v <= 2 * D:
            res += 3 * D - v
        else:
            res += D
    if res <= t:
        return True
    else:
        return False
#print(z)
if check(z[-1][1]) == False:
    print(-1)
    exit()

ok = len(z)-1
ng = -1

while ok - ng > 1:
    mid = (ok + ng) // 2
    if check(z[mid][1]):
        ok = mid
    else:
        ng = mid

print(z[ok][0])