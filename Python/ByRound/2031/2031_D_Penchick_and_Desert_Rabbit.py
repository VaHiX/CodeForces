# Contest 2031, Problem D: Penchick and Desert Rabbit
# URL: https://codeforces.com/contest/2031/problem/D

import sys

input = sys.stdin.readline


def fn():
    n = int(input())
    a = list(map(int, input().split()))

    ans = a.copy()
    for i, x in enumerate(ans):
        if i:
            ans[i] = max(ans[i], ans[i - 1])

    nextMin = a[-1]
    for i in range(n - 2, -1, -1):
        if ans[i] > nextMin:
            ans[i] = ans[i + 1]
        nextMin = min(nextMin, a[i])

    print(*ans)


for _ in range(int(input())):
    fn()
