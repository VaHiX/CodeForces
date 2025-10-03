# Contest 1949, Problem K: Make Triangle
# URL: https://codeforces.com/contest/1949/problem/K


import sys

input = lambda: sys.stdin.readline().strip()

t = int(input())
for _ in range(t):
    N, *n = map(int, input().split())
    a = [*map(int, input().split())]
    group = [[n[i], 0] for i in range(3)]
    ans = [[] for i in range(3)]
    a.sort()
    p = a[:] + [0, 0, 0]
    for i in range(1, N):
        p[i] += p[i - 1]

    S = (sum(a) + 1) // 2
    check = True

    for i in range(N - 1, -1, -1):
        tmp = False
        for j in range(3):
            if group[j][0] == 0:
                continue
            if group[j][1] + a[i] + p[group[j][0] - 2] >= S:
                continue

            group[j][0] -= 1
            group[j][1] += a[i]
            ans[j].append(a[i])
            tmp = True
            break

        if not tmp:
            check = False
            break

    if check:
        print("YES")
        for i in range(3):
            print(*ans[i])
    else:
        print("NO")
