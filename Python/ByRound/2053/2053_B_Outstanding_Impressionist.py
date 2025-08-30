# Contest 2053, Problem B: Outstanding Impressionist
# URL: https://codeforces.com/contest/2053/problem/B

import sys

input = sys.stdin.buffer.readline

for _ in range(int(input())):
    n = int(input())
    a = [tuple(map(int, input().split())) for _ in range(n)]
    ok = [1] * (2 * n + 1)
    ok[0] = 0
    blocked = [0] * (2 * n + 1)
    for l, r in a:
        if l == r:
            ok[l] = 0
            blocked[l] += 1
    for i in range(1, 2 * n + 1):
        ok[i] += ok[i - 1]
    ans = []
    for i, (l, r) in enumerate(a):
        free = ok[r] - ok[l - 1]
        if l == r and blocked[l] == 1:
            free += 1
        ans.append(int(free > 0))
    print("".join(map(str, ans)))
