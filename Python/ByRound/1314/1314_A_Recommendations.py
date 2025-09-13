# Contest 1314, Problem A: Recommendations
# URL: https://codeforces.com/contest/1314/problem/A

import sys, random

input = lambda: sys.stdin.readline().rstrip()


write = lambda x: sys.stdout.write(x + "\n")
writef = lambda x: print("{:.12f}".format(x))
debug = lambda x: sys.stderr.write(x + "\n")
YES = "Yes"
NO = "No"
pans = lambda v: print(YES if v else NO)
INF = 10**18
LI = lambda: list(map(int, input().split()))
II = lambda: int(input())


def debug(_l_):
    for s in _l_.split():
        print(f"{s}={eval(s)}", end=" ")
    print()


def dlist(*l, fill=0):
    if len(l) == 1:
        return [fill] * l[0]
    ll = l[1:]
    return [dlist(*ll, fill=fill) for _ in range(l[0])]


from heapq import heappop as hpp, heappush as hp

n = int(input())
a = list(map(int, input().split()))
t = LI()
index = list(range(n))
index.sort(key=lambda i: a[i])
a = [a[i] for i in index]
t = [t[i] for i in index]
p = -100
l = []
ans = 0
start = None


def sub(l, start):
    if start is None:
        return 0
    n = len(l)
    res = 0
    h = []
    total = 0
    j = 0
    for val in range(start, start + n):
        while j < n and a[l[j]] <= val:
            hp(h, -t[l[j]])
            total += t[l[j]]
            j += 1
        v = hpp(h)
        v *= -1
        total -= v
        res += total
    #         print(total,v)
    return res


for i in range(n):
    v = a[i]
    if v >= p:
        ans += sub(l, start)
        l = [i]
        p = v + 1
        start = v
    else:
        l.append(i)
        p += 1
ans += sub(l, start)
print(ans)
