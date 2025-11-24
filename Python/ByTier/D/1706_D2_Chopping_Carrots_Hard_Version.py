# Problem: CF 1706 D2 - Chopping Carrots (Hard Version)
# https://codeforces.com/contest/1706/problem/D2

import sys

input = sys.stdin.readline

for _ in range(int(input())):
    n, k = map(int, input().split())
    w = list(map(int, input().split()))
    d = [0] * (w[-1] + 1)

    for i in w:
        b = i
        j = 2
        while j <= k and j <= i:
            a = i // j
            d[a + 1] = max(b, d[a + 1])
            j = i // b + 1
            b = a

        a = i // j
        d[a + 1] = max(b, d[a + 1])

    c = e = w[-1] // k
    ans = w[-1] - w[0]

    for i in range(1, w[0] + 1):
        c = max(d[i], c)
        ans = min(ans, c - i)

    print(ans)


# https://github.com/VaHiX/CodeForces/