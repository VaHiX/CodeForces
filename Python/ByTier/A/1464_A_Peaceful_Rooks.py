# Contest 1464, Problem A: Peaceful Rooks
# URL: https://codeforces.com/contest/1464/problem/A

import sys, random
input = lambda : sys.stdin.readline().rstrip()

write = lambda x: sys.stdout.write(x+"\n"); writef = lambda x: print("{:.12f}".format(x))
debug = lambda x: sys.stderr.write(x+"\n")
YES="Yes"; NO="No"; pans = lambda v: print(YES if v else NO); inf=10**18
LI = lambda : list(map(int, input().split()))
def debug(_l_):
    for s in _l_.split():
        print(f"{s}={eval(s)}", end=" ")
    print()
def dlist(*l, fill=0):
    if len(l)==1:
        return [fill]*l[0]
    ll = l[1:]
    return [dlist(*ll, fill=fill) for _ in range(l[0])]
# sys.setrecursionlimit(3*10**5+10)

t = int(input())
for i in range(t):
    n,m = LI()
    xy = {}
    xs = set()
    for i in range(m):
        x,y = LI()
        xy[x] = y
        xs.add(x)
    ans = 0
    while xs:
        for u in xs:
            break
        if xy[u]==u:
            xs.remove(u)
            continue
        c = 1
        cur = set([u])
        xs.remove(u)
        while 1:
            v = xy[u]
            if v in cur:
                ans += c + 1
                break
            elif v not in xs:
                ans += c
                break
            xs.remove(v)
            cur.add(v)
            u = v
            c += 1
    print(ans)