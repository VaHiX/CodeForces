# Contest 1416, Problem A: k-Amazing Numbers
# URL: https://codeforces.com/contest/1416/problem/A

import sys

tt = int(sys.stdin.readline().strip())
for _ in range(tt):
    n = int(sys.stdin.readline().strip())

    f = [0] * (n + 1)
    last = [0] * (n + 1)
    ans = [-1] * (n + 1)
    
    arr = [0] + list(map(int, sys.stdin.readline().split()))

    for i in range(1, n + 1):
        x = arr[i]
        f[x] = max(f[x], i - last[x])
        last[x] = i

    for x in range(1, n + 1):
        f[x] = max(f[x], n - last[x] + 1)
        
        for i in range(f[x], n + 1):
            if ans[i] == -1:
                ans[i] = x
            else:
                break

    print(" ".join(map(str, ans[1:])))