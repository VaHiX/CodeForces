# Contest 662, Problem A: Gambling Nim
# URL: https://codeforces.com/contest/662/problem/A

import sys 
input = sys.stdin.buffer.readline
 
n = int(input())
goal = 0
C = []
for _ in range(n):
    a,b = [int(x) for x in input().split()]
    C.append(a ^ b)
    goal ^= a
 
base = []
for c in C:
    for b in base:
        c = min(c, c ^ b)
    if c:
        base.append(c)
 
for b in base:
    goal = min(goal, goal ^ b)
 
if goal:
    print('1/1')
else:
    m = len(base)
    print(2**m - 1, '/', 2**m, sep = '')