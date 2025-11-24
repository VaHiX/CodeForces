# Problem: CF 1071 A - Cram Time
# https://codeforces.com/contest/1071/problem/A

import sys

input = lambda: sys.stdin.readline()
mi = lambda: map(int, input().split())
li = lambda: list(mi())
a, b = mi()
ok = 0
ng = 10**9
while ng - ok > 1:
    mid = (ok + ng) // 2
    if mid * (mid + 1) // 2 <= a + b:
        ok = mid
    else:
        ng = mid
n = ok
p = []
q = []
for i in range(1, n + 1)[::-1]:
    if i <= a:
        p.append(i)
        a -= i
    else:
        q.append(i)
assert sum(q) <= b
p.sort()
q.sort()
print(len(p))
print(*p)
print(len(q))
print(*q)


# https://github.com/VaHiX/CodeForces/