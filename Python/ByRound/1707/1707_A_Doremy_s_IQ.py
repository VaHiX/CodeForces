# Contest 1707, Problem A: Doremy's IQ
# URL: https://codeforces.com/contest/1707/problem/A

import sys

input = sys.stdin.readline
ans = []
for _ in range(int(input())):
    n, q = map(int, input().split())
    a = list(map(int, input().split()))
    ll = [0] * n
    curr = 0
    for i in range(n - 1, -1, -1):
        if curr != q:
            ll[i] = 1
            if a[i] > curr:
                curr += 1
        else:
            if a[i] <= curr:
                ll[i] = 1
    ans.append("".join(map(str, ll)))
print("\n".join(ans))
