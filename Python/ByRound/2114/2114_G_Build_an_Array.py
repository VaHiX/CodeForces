# Contest 2114, Problem G: Build an Array
# URL: https://codeforces.com/contest/2114/problem/G

import sys

input = lambda: sys.stdin.readline().rstrip()


for _ in range(int(input())):
    n, k = map(int, input().split())
    w = list(map(int, input().split()))
    a = []
    b = []
    for i in range(n):
        c, x = 0, w[i]
        while x % 2 == 0:
            x //= 2
            c += 1
        a.append(x)
        b.append(2**c)

    l = [0] * (n + 1)
    r = [0] * (n + 1)
    x, c = a[0], 0
    for i in range(n):
        l1 = b[i]
        if a[i] == x and i > 0 and b[i - 1] < b[i]:
            l1 -= 2 * b[i - 1] - 1

        if a[i] != x:
            x = a[i]
        l[i] += l[i - 1] + l1

    l[n] = l[n - 1]
    x = a[-1]
    for i in range(n - 1, -1, -1):
        r1 = b[i]
        if a[i] == x and i < n - 1 and b[i] > b[i + 1]:
            r1 -= 2 * b[i + 1] - 1

        if a[i] != x:
            x = a[i]
        r[i] += r[i + 1] + r1

    r[-1] = r[0]
    for i in range(n):
        c = max(c, l[n] - l[i] + r[-1] - r[i] + b[i])

    print(["NO", "YES"][c >= k])
