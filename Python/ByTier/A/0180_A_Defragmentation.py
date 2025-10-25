# Contest 180, Problem A: Defragmentation
# URL: https://codeforces.com/contest/180/problem/A

import sys

input = sys.stdin.readline
from collections import defaultdict, deque, Counter
from heapq import heappop, heappush
from bisect import bisect_left, bisect_right
from math import gcd


n, m = map(int, input().split())

a = [list(map(int, input().split())) for i in range(m)]

tot = 0
vac = []
use = set()
for i in range(m):
    ni, ai = a[i][0], a[i][1:]
    tot += ni
    for j in range(ni):
        use.add(ai[j])

for i in range(1, n + 1):
    if i not in use:
        vac.append(i)
vac = vac[::-1]

ans = []
now = 1
d = defaultdict(int)
for i in range(m):
    ni, ai = a[i][0], a[i][1:]
    for j in range(ni):
        if ai[j] > tot:
            pre = ai[j]
            ai[j] = vac.pop()
            ans.append((pre, ai[j]))
        d[now] = ai[j]
        now += 1
v = [0] * (n + 1)
for i in range(1, tot + 1):
    if v[i]:
        continue
    ord = [i]
    v[i] = 1
    for i in range(tot - 1):
        if v[d[ord[-1]]]:
            continue
        ord.append(d[ord[-1]])
        v[ord[-1]] = 1
    ord = ord
    if len(ord) == 1:
        continue
    ans.append((ord[0], tot + 1))
    for i in range(1, len(ord)):
        ans.append((ord[i], ord[i - 1]))
    ans.append((tot + 1, ord[-1]))

print(len(ans))
for i, j in ans:
    print(i, j)
