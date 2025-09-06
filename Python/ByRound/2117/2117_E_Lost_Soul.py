# Contest 2117, Problem E: Lost Soul
# URL: https://codeforces.com/contest/2117/problem/E

import sys

input = lambda: sys.stdin.readline().rstrip()


for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split())) + [n + 1]
    b = list(map(int, input().split())) + [n + 1]
    q = [0] * (n + 2)
    for i in range(n - 1, -1, -1):
        if a[i] == b[i] or a[i] == a[i + 1] or b[i] == b[i + 1] or q[a[i]] or q[b[i]]:
            print(i + 1)
            break
        if i < n - 1:
            q[a[i + 1]] = 1
            q[b[i + 1]] = 1
    else:
        print(0)
