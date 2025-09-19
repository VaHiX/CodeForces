# Contest 2106, Problem C: Cherry Bomb
# URL: https://codeforces.com/contest/2106/problem/C

import sys

input = sys.stdin.buffer.readline

for _ in range(int(input())):
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    if b.count(-1) == n:
        print(k - max(a) + min(a) + 1)
    else:
        f, s = 1, 0
        for i in range(n):
            if b[i] != -1:
                s = a[i] + b[i]
        for i in range(n):
            if (b[i] != -1 and a[i] + b[i] != s) or (
                b[i] == -1 and not (0 <= s - a[i] <= k)
            ):
                f = 0
        print(f)
