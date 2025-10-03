# Contest 3, Problem D: Least Cost Bracket Sequence
# URL: https://codeforces.com/contest/3/problem/D

import sys
from heapq import heappush, heappop

input = lambda: sys.stdin.readline().rstrip()
# sys.stdin = open('../input.txt', 'r')
I = lambda: int(input())
MI = lambda: map(int, input().split())
GMI = lambda: map(lambda x: int(x) - 1, input().split())
LI = lambda: list(MI())
LGMI = lambda: list(GMI())
YN = lambda x: print("YES" if x else "NO")
mod = 1000000007
mod2 = 998244353

s = list(input())
n = len(s)
m = s.count("?")
costs = [LI() for _ in range(m)]
j = 0
cost = 0
balance = 0

h = []

for i in range(n):
    if s[i] == "(":
        balance += 1
    elif s[i] == ")":
        balance -= 1
    else:
        a, b = costs[j]
        j += 1
        s[i] = ")"
        cost += b
        balance -= 1
        heappush(h, (a - b, i))
    if balance < 0:
        if not h:
            exit(print(-1))
        diff, idx = heappop(h)
        s[idx] = "("
        cost += diff
        balance += 2
if balance == 0:
    print(cost)
    print("".join(s))
else:
    print(-1)
