# Contest 2065, Problem E: Skibidus and Rizz
# URL: https://codeforces.com/contest/2065/problem/E

import sys

input = lambda: sys.stdin.readline().strip()


def printl(l):
    print("".join(str(y) for y in l))


def rl():
    return map(int, input().split())


for _ in range(int(input())):
    n, m, k = rl()

    if k < abs(n - m) or k > max(m, n):
        print(-1)
        continue
    if n >= m:
        a = k * [0] + (n - k) * [1, 0] + (m - n + k) * [1]
    else:
        a = k * [1] + (m - k) * [0, 1] + (n - m + k) * [0]
    print("".join(str(i) for i in a))
