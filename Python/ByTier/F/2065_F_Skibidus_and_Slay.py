# Contest 2065, Problem F: Skibidus and Slay
# URL: https://codeforces.com/contest/2065/problem/F

import sys

input = lambda: sys.stdin.readline().rstrip()


for _ in range(int(input())):
    n = int(input())
    h = list(map(int, input().split()))
    d = [[i] for i in range(n)]
    for _ in range(n - 1):
        a, b = map(lambda x: int(x) - 1, input().split())
        d[a].append(b)
        d[b].append(a)
    q = [0] * n
    for i in range(n):
        w = sorted([h[j] for j in d[i]])
        for j in range(len(w) - 1):
            if w[j] == w[j + 1]:
                q[w[j] - 1] = 1
    print("".join(map(str, q)))
