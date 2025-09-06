# Contest 2052, Problem D: DAG Serialization
# URL: https://codeforces.com/contest/2052/problem/D

import sys
from collections import deque

input = sys.stdin.readline

n = int(input())

adj = [[] for _ in range(n)]
cnt = [0] * n
type_ = [0] * n
p = [
    "unset false",
    "set true",
    "set false",
    "unset true",
]
for i in range(n):
    x = input().strip()
    type_[i] = p.index(x)

m = int(input())
for _ in range(m):
    u, v = map(int, input().split())
    u -= 1
    v -= 1
    adj[u].append(v)
    cnt[v] += 1
queue = [deque() for _ in range(4)]
for i in range(n):
    if cnt[i] == 0:
        queue[type_[i]].append(i)
ans = []
for case in [0, 1, 2, 3, 0]:
    while queue[case]:
        u = queue[case].pop()
        ans.append(u)
        for v in adj[u]:
            cnt[v] -= 1
            if cnt[v] == 0:
                queue[type_[v]].append(v)
reg = 0
verify = True
for i in ans:
    if reg:
        if type_[i] == 2:
            pass
        elif type_[i] == 3:
            reg = 0
        else:
            verify = False
            break
    else:
        if type_[i] == 0:
            pass
        elif type_[i] == 1:
            reg = 1
        else:
            verify = False
            break

if verify and len(ans) == n:
    print(*[k + 1 for k in ans])
else:
    print(-1)
