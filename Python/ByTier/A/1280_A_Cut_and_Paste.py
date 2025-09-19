# Contest 1280, Problem A: Cut and Paste
# URL: https://codeforces.com/contest/1280/problem/A

import sys

input = lambda: sys.stdin.readline().strip()


def I():
    return input()


def II():
    return int(input())


def MII():
    return map(int, input().split())


def LI():
    return list(input().split())


def LII():
    return list(map(int, input().split()))


def LFI():
    return list(map(float, input().split()))


def GMI():
    return map(lambda x: int(x) - 1, input().split())


def LGMI():
    return list(map(lambda x: int(x) - 1, input().split()))


fmax = lambda x, y: x if x > y else y
fmin = lambda x, y: x if x < y else y

MOD = 10**9 + 7
t = II()
outs = []

for _ in range(t):
    x = II()
    s = I()
    n = len(s)

    tmp = [0] * x
    for i in range(fmin(n, x)):
        tmp[i] = int(s[i]) - 1
    l = 0
    while n < x and l < x:
        left = n
        right = min(x, n + (n - l - 1) * tmp[l])
        for i in range(left, right):
            tmp[i] = tmp[i - (n - l - 1)]
        # s += s[l + 1:] * cur
        n += (n - l - 1) * tmp[l] % MOD
        l += 1

    while l < x:
        n += (n - l - 1) * tmp[l] % MOD
        l += 1

    outs.append(n % MOD)

print("\n".join(map(str, outs)))
