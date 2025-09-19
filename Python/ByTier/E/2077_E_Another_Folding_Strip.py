# Contest 2077, Problem E: Another Folding Strip
# URL: https://codeforces.com/contest/2077/problem/E

from sys import stdin

input = lambda: stdin.readline()[:-1]


def calc(a):
    B = a.copy()
    n = len(a)
    if n == 0:
        return 0
    ans = 0
    while max(a) > 0:
        idx = -1
        for i in range(n):
            if a[i] > 0:
                idx = i
                break
        ans += 1
        now = idx - 1
        for i in range(n):
            if a[i] > 0 and (i - now) % 2 == 1:
                a[i] -= 1
                now = i
    print(B, ans)
    return ans


mod = 998244353


def solve(n, a):
    ans = 0
    stc = [[] for i in range(2)]
    for i in range(n):
        l = i + 1
        r = n - i
        rem = a[i]
        ans += rem * l * r
        ans %= mod

        p = (i + 1) % 2
        while rem > 0 and len(stc[p]) > 0:
            sz, idx = stc[p].pop()
            use = min(sz, rem)
            sz -= use
            rem -= use
            ans -= (idx + 1) * r * use
            ans %= mod
            if sz > 0:
                stc[p].append((sz, idx))
        stc[i & 1].append((a[i], i))
    return ans


def naive(n, a):
    ans = 0
    for l in range(n):
        for r in range(n):
            ans += calc(a[l : r + 1])
    return ans


import random

while False:
    n = random.randint(1, 4)
    a = [random.randint(1, 3) for i in range(n)]
    ans1 = solve(n, a)
    ans2 = naive(n, a)
    if ans1 != ans2:
        print(n, a, ans1, ans2)
        exit()


for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    print(solve(n, a) % mod)
