# Contest 1744, Problem A: Number Replacement
# URL: https://codeforces.com/contest/1744/problem/A

import sys

ip = sys.stdin.readline
R = lambda: list(map(int, ip().split()))
for _ in range(int(ip())):
    n = int(ip())
    a = R()
    s = ip()
    res = [0] * (51)
    for i in range(n):
        res[a[i]] = s[i]
    for i in range(n):
        if res[a[i]] != s[i]:
            print("NO")
            break
    else:
        print("YES")
