# Contest 1628, Problem A: Meximum Array
# URL: https://codeforces.com/contest/1628/problem/A

import sys
input = sys.stdin.readline


for _ in range(int(input())):
    n = int(input())
    w = list(map(int, input().split()))
    ans = []
    d = [[] for _ in range(n+1)]
    for i in range(n-1, -1, -1):
        d[w[i]].append(i)
    s = 0
    while s < n:
        x = s
        for i in range(n+1):
            while d[i] and d[i][-1] < s:
                d[i].pop()

            if d[i] == []:
                ans.append(i)
                s = x+1
                break
            else:
                x = max(x, d[i][-1])
    print(len(ans))
    print(' '.join(map(str, ans)))
