# Contest 2082, Problem D: Balancing
# URL: https://codeforces.com/contest/2082/problem/D


import sys

input = sys.stdin.readline

for _ in range(int(input())):
    n = int(input())
    l1 = list(map(int, input().split()))
    cnt = 0
    for i in range(n - 1):
        if l1[i] >= l1[i + 1]:
            cnt += 1
    ans = (cnt + 1) // 2
    if ans == 0:
        print(ans)
        continue
    l = -1
    r = -1
    for i in range(n - 1):
        if l1[i] >= l1[i + 1]:
            l = i
            break
    for i in range(n - 1, 0, -1):
        if l1[i - 1] >= l1[i]:
            r = i
            break
    if l1[r] - l1[l] < r - l and cnt % 2 == 0:
        ans += 1

    print(ans)
