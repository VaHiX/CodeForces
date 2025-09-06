# Contest 1589, Problem A: Mathematical Addition
# URL: https://codeforces.com/contest/1589/problem/A

from sys import stdin

for _ in range(int(input())):
    u, v = map(int, stdin.readline().split())
    print(-u ** 2, v ** 2)
