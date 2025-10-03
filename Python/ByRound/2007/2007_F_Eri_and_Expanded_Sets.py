# Contest 2007, Problem F: Eri and Expanded Sets
# URL: https://codeforces.com/contest/2007/problem/F

import random
from math import gcd
MAXN = 400_000
lg = [0] * (MAXN + 1)
lg[1] = 0
for c in range(2, MAXN + 1):
    lg[c] = lg[c // 2] + 1


def main():
    n = int(input())
    # n = 1
    n -= 1
    a = list(map(int, input().split()))
    # a = [random.randint(1, 10) for _ in range(n+1)]
    # for i in range(1, n):
    #     if random.random() < 0.1:
    #         a[i] = a[i - 1]
    ans = n + 1
    k = lg[n]
    st = [[0] * n for _ in range(k + 1)]
    for i in range(n):
        st[0][i] = abs(a[i] - a[i + 1])
    for i in range(1, k + 1):
        for j in range(n - (1 << i) + 1):
            st[i][j] = gcd(st[i - 1][j], st[i - 1][j + (1 << (i-1))])

    def q(L, R):
        sz = lg[R - L + 1]
        return gcd(st[sz][L], st[sz][R - (1 << sz) + 1])

    def ok(val):
        if val & (val - 1):
            return False
        return True

    # handle zeros separately
    l = 0
    for r in range(n):
        if st[0][r]:
            l = r
            continue
        while st[0][l]:
            l += 1
        ans += r - l + 1

    l = 0
    for r in range(n):
        while l <= r and st[0][r] and ok(q(l, r)): # dont move the l pointer when cur value is zero
            l += 1
        if l != 0 and ok(q(l-1, r)):
            ans += l

    # temp = n + 1
    # for r in range(n):
    #     for l in range(r + 1):
    #         if ok(q(l, r)):
    #             temp += 1
    # assert ans == temp, (ans, temp, *a)
    print(ans)

# t = 1
t = int(input())
for _ in range(t):
    main()
