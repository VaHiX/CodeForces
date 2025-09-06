# Contest 2023, Problem A: Concatenation of Arrays
# URL: https://codeforces.com/contest/2023/problem/A

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n = int(input())
    X = [list(map(int, input().split())) for _ in range(n)]
    X.sort(key=lambda x: x[1] + x[0])
    Y = []
    for i in X:
        Y += i
    print(*Y)
