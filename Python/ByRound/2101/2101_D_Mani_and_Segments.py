# Contest 2101, Problem D: Mani and Segments
# URL: https://codeforces.com/contest/2101/problem/D

import sys

input = sys.stdin.readline

for _ in range(int(input())):
    n, s = int(input()), 0
    a = [0] + list(map(int, input().split()))
    l = [0] * (n + 1)
    c, s1, s2 = [0] * (n + 1), [], []
    for i in range(1, n + 1):
        l[i] = l[i - 1]
        while s1 and a[s1[-1]] < a[i]:
            p = s1.pop()
            c[p] -= 1
            if not c[p]:
                l[i] = max(l[i], p)
        while s2 and a[s2[-1]] > a[i]:
            p = s2.pop()
            c[p] -= 1
            if not c[p]:
                l[i] = max(l[i], p)
        s1.append(i)
        s2.append(i)
        c[i] = 2
    a = [0] + a[1:][::-1]
    r = [0] * (n + 1)
    c, s1, s2 = [0] * (n + 1), [], []
    for i in range(1, n + 1):
        r[i] = r[i - 1]
        while s1 and a[s1[-1]] < a[i]:
            p = s1.pop()
            c[p] -= 1
            if not c[p]:
                r[i] = max(r[i], p)
        while s2 and a[s2[-1]] > a[i]:
            p = s2.pop()
            c[p] -= 1
            if not c[p]:
                r[i] = max(r[i], p)
        s1.append(i)
        s2.append(i)
        c[i] = 2
    r = [0] + r[1:][::-1]
    for i in range(1, n + 1):
        r[i] = n - r[i] + 1
    for i in range(1, n + 1):
        s += (i - l[i]) * (r[i] - i)
        if i > 1:
            s -= (i - 1 - l[i]) * (r[i - 1] - i)
    print(s)
