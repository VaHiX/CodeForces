# Contest 2048, Problem D: Kevin and Competition Memories
# URL: https://codeforces.com/contest/2048/problem/D

import sys

input = lambda: sys.stdin.readline().rstrip()


for _ in range(int(input())):
    n, m = map(int, input().split())
    a = list(map(int, input().split()))
    b = sorted(map(int, input().split()))
    q = []
    for i in a:
        if i > a[0]:
            q.append(i)
    q.sort()
    d = []
    n, j = len(q), 0
    for i in b:
        if i <= a[0]:
            d.append(1)
        else:
            while j < n and i > q[j]:
                j += 1
            d.append(n - j + 1)
    d.sort()
    for i in range(1, m + 1):
        c = 0
        for j in range(i - 1, m, i):
            c += d[j]
        print(c, end=" ")
    print()
