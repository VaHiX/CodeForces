# Contest 2113, Problem A: Shashliks
# URL: https://codeforces.com/contest/2113/problem/A

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n, a, b, x, y = map(int, input().split())
    if x > y:
        a, b = b, a
        x, y = y, x
    ans = 0
    if a <= n:
        ans += (n - a) // x + 1
        n -= x * ans
    if b <= n:
        ans += (n - b) // y + 1
    print(ans)
