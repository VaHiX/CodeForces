# Contest 2093, Problem F: Hackers and Neural Networks
# URL: https://codeforces.com/contest/2093/problem/F

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n, m = map(int, input().split())
    a = list(input().split())
    b = []
    cnt = [0] * n
    ans = 0
    for i in range(m):
        b.append(list(input().split()))
        ans2 = 0
        for j in range(n):
            if b[i][j] == a[j]:
                cnt[j] += 1
                ans2 += 1
        ans = max(ans, ans2)
    if min(cnt) == 0:
        print(-1)
        continue
    print(n + 2 * (n - ans))
