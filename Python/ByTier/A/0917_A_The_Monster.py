# Contest 917, Problem A: The Monster
# URL: https://codeforces.com/contest/917/problem/A

import sys
input = lambda: sys.stdin.readline().rstrip()
ii = lambda: int(input())
lii = lambda: list(map(int, input().split()))

s = input()
n = len(s)
ans = 0
for i in range(n):
    left, mark = 0, 0
    for j in range(i, n):
        if s[j] == '(':
            left += 1
        elif s[j] == ')':
            left -= 1
        else:
            left -= 1
            mark += 1
        if left < 0:
            if mark == 0:
                break
            mark -= 1
            left += 2
        if left == 0:
            ans += 1

print(ans)
