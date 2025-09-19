# Contest 2103, Problem D: Local Construction
# URL: https://codeforces.com/contest/2103/problem/D

import sys

input = lambda: sys.stdin.readline().rstrip()


for _ in range(int(input())):
    n = int(input())
    w = list(map(int, input().split()))
    x = max(w) + 1
    d = [[] for _ in range(n)]
    for i in range(n):
        if w[i] == -1:
            a = i
        else:
            d[w[i] - 1].append(i)

    l, r, ew = 1, n, [0] * n
    for i in range(n):
        for j in d[i]:
            if j < a:
                if i % 2:
                    ew[j] = l
                    l += 1
                else:
                    ew[j] = r
                    r -= 1
            else:
                break
        for j in d[i][::-1]:
            if j > a:
                if i % 2:
                    ew[j] = l
                    l += 1
                else:
                    ew[j] = r
                    r -= 1
    ew[a] = l
    print(" ".join(map(str, ew)))
