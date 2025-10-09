# Contest 442, Problem A: Borya and Hanabi
# URL: https://codeforces.com/contest/442/problem/A

import sys

input = sys.stdin.readline


n = int(input())
w = {(1 << "RGBYW".index(i[0])) + (1 << int(i[1]) + 4) for i in input()[:-1].split()}
m = len(w)
c = 8
for i in range(1024):
    if len({i & j for j in w}) == m:
        c = min(c, bin(i)[2:].count("1"))
print(c)
