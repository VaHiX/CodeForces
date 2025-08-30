# Contest 2055, Problem D: Scarecrow
# URL: https://codeforces.com/contest/2055/problem/D

import sys

input = lambda: sys.stdin.readline().strip()
out = []
tests = int(input())
for _ in range(tests):
    n, k, l = map(int, input().split())
    k *= 2
    l *= 2
    v = k
    a = list(map(lambda x: 2 * int(x), input().split()))
    ans = a[0]
    for i in range(1, n):
        if a[i] > v:
            a[i] = max(v, a[i] - ans)
            ans += (a[i] - v) // 2
            v = (v + a[i]) // 2 + k
        else:
            a[i] = min(v, a[i] + ans)
            v = a[i] + k
    if v < l:
        ans += l - v
    out.append(ans)
print(*out, sep="\n")
