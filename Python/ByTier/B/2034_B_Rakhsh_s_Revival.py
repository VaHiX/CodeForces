# Contest 2034, Problem B: Rakhsh's Revival
# URL: https://codeforces.com/contest/2034/problem/B

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n, m, k = map(int, input().split())
    s = input()
    j = 0
    cnt = 0
    cur = 0
    while j < n:
        if s[j] == "1":
            cur = 0
            j += 1
        else:
            cur += 1
            if cur == m:
                cur = 0
                cnt += 1
                j += k
            else:
                j += 1
    print(cnt)
