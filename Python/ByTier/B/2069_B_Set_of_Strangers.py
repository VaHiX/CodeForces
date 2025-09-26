# Contest 2069, Problem B: Set of Strangers
# URL: https://codeforces.com/contest/2069/problem/B

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    x, y = map(int, input().split())
    final = [[*(map(int, input().split()))] for __ in range(x)]
    hash1 = (x * y + 1) * [0]
    for i in range(x):
        for j in range(y):
            c = final[i][j]
            hash1[c] = max(hash1[c], 1)
            if i > 0 and final[i - 1][j] == c or j > 0 and final[i][j - 1] == c:
                hash1[c] = 2
    vals = hash1
    if len(vals) == 1:
        print(0)
    else:
        print(sum(vals) - max(vals))
