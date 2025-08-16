# Contest 2120, Problem G: Eulerian Line Graph
# URL: https://codeforces.com/contest/2120/problem/G

import sys
import heapq
import math
import random
from itertools import *
from collections import deque
input = sys.stdin.readline
def fg():
    return int(input())
def fgh():
    return [int(xx) for xx in input().split()]
def tt():
    sys.stdout.flush()
def sd():
    print('Yes')
def df():
    print('No')
for __ in range(fg()):
    n, m, k = fgh()
    a = [[] for i in range(n)]
    for i in range(m):
        u, v = fgh()
        u -= 1
        v -= 1
        a[u].append(v)
        a[v].append(u)
    cnt = 0
    for i in range(n):
        if len(a[i]) % 2:
            cnt += 1
    if cnt == 0:
        sd()
    else:
        cnt1 = 0
        cnt2 = 0
        powpow = 0
        d = [[0] * 2 for i in range(n)]
        for i in range(n):
            for j in a[i]:
                d[i][len(a[j]) % 2] += 1
                if (len(a[i]) + len(a[j])) % 2 == 0:
                    cnt2 += 1
                else:
                    cnt1 += 1
        if k == 1:
            if cnt1 <= 4:
                sd()
            else:
                df()
            continue
        if cnt2 == 0:
            sd()
        else:
            if cnt1 == 0:
                sd()
                continue
            zz = 0
            for i in range(n):
                zz += (d[i][0] * d[i][1])
            if k == 2:
                if zz <= 2:
                    sd()
                else:
                    df()
                continue
            if zz == 0:
                sd()
                continue
            
            zzz = 0
            for i in range(n):
                zzz += 2 * d[i][0] * d[i][1] * (len(a[i]) - 2)
            for i in range(n):
                for j in a[i]:
                    W = ((len(a[i]) % 2) ^ (len(a[j]) % 2))
                    uy = 1 ^ W
                    for p in range(2):
                        xx = d[i][p]
                        yy = d[j][p ^ uy]
                        if len(a[j]) % 2 == p:
                            xx -= 1
                        if len(a[i]) % 2 == (p ^ uy):
                            yy -= 1
                        zzz += xx * yy
            zzz //= 2
            
            if k == 3:
                if zzz <= 2:
                    sd()
                else:
                    df()
                continue

            if zzz == 0:
                sd()
                continue
            if zz >= 4:
                df()
                continue
            if zzz >= 4:
                df()
                continue
            q = deque()
            dist = [n] * n
            for i in range(n):
                if len(a[i]) == 1:
                    q.append(i)
                    dist[i] = 0
            while q:
                c = q.popleft()
                for u in a[c]:
                    if dist[u] > dist[c] + 1:  
                        dist[u] = dist[c] + 1
                        q.append(u)
            mn = n
            for i in range(n):
                if len(a[i]) > 2:
                    mn = min(mn, dist[i])
            if mn >= k:
                sd()
            else:
                df()


