# Contest 1687, Problem A: The Enchanted Forest
# URL: https://codeforces.com/contest/1687/problem/A

import sys, os, io
input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

t = int(input())
ans = []
for _ in range(t):
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    for i in range(n):
        a[i] += k - 1
    k = min(n, k)
    cnt = [0]
    for i in a:
        cnt.append(i + cnt[-1])
    ans0 = 0
    x = k * (k - 1) // 2
    for i in range(k, n + 1):
        ans0 = max(cnt[i] - cnt[i - k] - x, ans0)
    ans.append(ans0)
sys.stdout.write("\n".join(map(str, ans)))