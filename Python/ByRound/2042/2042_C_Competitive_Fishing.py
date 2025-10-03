# Contest 2042, Problem C: Competitive Fishing
# URL: https://codeforces.com/contest/2042/problem/C

import sys

input = lambda: sys.stdin.readline()[:-1]

for _ in [0] * int(input()):
    n, k = map(int, input().split())
    s = input()
    l = [0]
    for i in s[::-1]:
        l += (l[-1] + (i == "1") * 2 - 1,)
    l = l[-2:0:-1]
    l.sort()
    ans = 1
    while l and 0 < k:
        k -= l.pop()
        ans += 1
    if 0 < k:
        print(-1)
    else:
        print(ans)
