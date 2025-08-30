# Contest 1817, Problem A: Almost Increasing Subsequence
# URL: https://codeforces.com/contest/1817/problem/A

import io
import os

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline
n, q = input().split()
n = int(n)
q = int(q)
l = [int(num) for num in input().split()]
l0 = []
c = 0
for i in range(len(l) - 2):
    if l[i] >= l[i + 1] and l[i + 1] >= l[i + 2]:
        l[i] = 0
        c = c + 1
    l0.append(c)
for i in range(q):
    a, b = input().split()
    a = int(a)
    b = int(b)
    if a > 1 and b - a > 1:
        print(b - a + 1 - l0[b - 3] + l0[a - 2])
    elif a > 1 and b - a == 1:
        print("2")
    elif a > 1 and a == b:
        print("1")
    elif a == 1 and b - a > 1:
        print(b - a + 1 - l0[b - 3])
    elif a == 1 and b - a == 1:
        print("2")
    elif a == 1 and a == b:
        print("1")
