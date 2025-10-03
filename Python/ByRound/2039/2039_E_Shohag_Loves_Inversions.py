# Contest 2039, Problem E: Shohag Loves Inversions
# URL: https://codeforces.com/contest/2039/problem/E

import sys

input = lambda: sys.stdin.readline().strip()


p = 998244353


T = int(input())
for _ in range(T):
    n = int(input())
    ans = 0
    if n == 2:
        print(1)
    else:
        s = 1
        ans = 0
        for i in range(2, n):
            if i <= 3:
                ans += i
                ans %= p
                s += i
                s %= p
            else:
                ans += i + (s - i) * (i + 1)
                ans %= p
                s += (s - i + 1) * i
                s %= p
        print(ans)
