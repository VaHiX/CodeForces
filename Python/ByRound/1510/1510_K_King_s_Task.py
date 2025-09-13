# Contest 1510, Problem K: King's Task
# URL: https://codeforces.com/contest/1510/problem/K

import sys

input = sys.stdin.readline
n = 2 * (int(input()))
a = [int(i) for i in input().split()]
b = [i for i in range(1, n + 1)]
ans = 0
for i in range(n):
    if a != b:
        if a[0] < a[n // 2]:
            for i in range(0, n - 1, 2):
                a[i], a[i + 1] = a[i + 1], a[i]
        else:
            x = n // 2
            a = a[x:] + a[:x]
        ans += 1
        # print(a)
    else:
        break
if a == b:
    print(ans)
else:
    print(-1)
