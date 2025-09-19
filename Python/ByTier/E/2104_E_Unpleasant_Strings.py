# Contest 2104, Problem E: Unpleasant Strings
# URL: https://codeforces.com/contest/2104/problem/E

from sys import stdin

input = lambda: stdin.readline().rstrip("\r\n")
from bisect import bisect_right

n, k = map(int, input().split())
s = input()
pos = [[] for _ in range(k)]

for i, x in enumerate(s, start=1):
    pos[ord(x) - ord("a")] += (i,)

last = [n + 1] * k
f = [0] * (n + 1)

for i in range(n, -1, -1):
    best = n + 1
    ind = 0
    for j in last:
        if j > n:
            ind = 1
            break
        if f[j] < best:
            best = f[j]
    else:
        ind = best + 1
    f[i] = ind

    if i > 0:
        last[ord(s[i - 1]) - ord("a")] = i

for _ in range(int(input())):
    p = 0
    for x in input():
        a = pos[ord(x) - ord("a")]
        j = bisect_right(a, p)
        if j == len(a):
            p = n + 1
            break
        p = a[j]

    print(0 if p > n else f[p])
