# Contest 1246, Problem A: p-binary
# URL: https://codeforces.com/contest/1246/problem/A

import sys

input = lambda: sys.stdin.readline()[:-1]
ni = lambda: int(input())
na = lambda: list(map(int, input().split()))
yes = lambda: print("yes")
Yes = lambda: print("Yes")
YES = lambda: print("YES")
no = lambda: print("no")
No = lambda: print("No")
NO = lambda: print("NO")
#######################################################################

n, p = na()

for k in range(100):
    x = n - k * p
    if x < k:
        continue
    y = 0
    while x:
        y += x % 2
        x //= 2
    if y <= k:
        print(k)
        exit()
print(-1)
