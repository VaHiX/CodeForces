# Contest 2039, Problem B: Shohag Loves Strings
# URL: https://codeforces.com/contest/2039/problem/B

from sys import stdin

input = lambda: stdin.readline()[:-1]


def solve():
    s = input()
    n = len(s)
    for i in range(n - 1):
        if s[i] == s[i + 1]:
            print(s[i] + s[i + 1])
            return
    for i in range(n - 2):
        if s[i] != s[i + 2]:
            print(s[i : i + 3])
            return
    print(-1)


for _ in range(int(input())):
    solve()
