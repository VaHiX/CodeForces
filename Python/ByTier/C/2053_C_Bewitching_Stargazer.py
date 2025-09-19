# Contest 2053, Problem C: Bewitching Stargazer
# URL: https://codeforces.com/contest/2053/problem/C

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n, k = map(int, input().split())
    v = n + 1
    seg, cnt = 1, 0
    while n >= k:
        cnt += seg * (n % 2)
        n //= 2
        seg *= 2
    print(cnt * v // 2)
