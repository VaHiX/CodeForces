# Contest 2050, Problem D: Digital string maximization
# URL: https://codeforces.com/contest/2050/problem/D

import sys

input = lambda: sys.stdin.readline().rstrip()

t = int(input())
for _ in range(t):
    s = [*map(int, list(input()))]
    for i in range(1, len(s)):
        j = i
        while j > 0 and s[j] - 1 > s[j - 1]:
            s[j - 1], s[j] = s[j] - 1, s[j - 1]
            j -= 1
    print("".join(map(str, s)))
