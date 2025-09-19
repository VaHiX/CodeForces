# Contest 2107, Problem F1: Cycling (Easy Version)
# URL: https://codeforces.com/contest/2107/problem/F1

import sys

input = sys.stdin.readline
inp = lambda: int(input())
insl = lambda: [*map(int, input().split())]
from collections import deque


def greedy(arrr):
    arr = [*arrr]
    res = arr[0]
    for i in range(1, len(arr)):  # about to jump over i
        if arr[i - 1] < arr[i]:
            arr[i], arr[i - 1] = arr[i - 1], arr[i]
            res += 1
        res += arr[i]

    return res


t = inp()
for _ in range(t):
    n = inp()
    a = insl()
    a = a[::-1]

    if len(set(a)) == 1:
        print(a[0] * n)
        continue

    x, y, *_ = sorted([*set(a)])
    xi, yi = a.index(x), a.index(y)
    print(
        min(
            greedy(a),
            xi + greedy([x] + a[:xi] + a[xi + 1 :]),
            yi + greedy([y] + a[:yi] + a[yi + 1 :]),
        )
    )
