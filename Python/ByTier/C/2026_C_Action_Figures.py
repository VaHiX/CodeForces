# Contest 2026, Problem C: Action Figures
# URL: https://codeforces.com/contest/2026/problem/C

import sys

input = sys.stdin.readline
Q = int(input())
for _ in range(Q):
    N = int(input())
    S = input()[:-1]
    result = N * (N + 1) // 2
    count = 0
    for i in range(N - 1, -1, -1):
        if S[i] == "1":
            if i + count - 1 < 0:
                count += 1
            else:
                count -= 1
                result -= i + 1
        else:
            count += 1
            if count > 0:
                count = 0
    print(result)
