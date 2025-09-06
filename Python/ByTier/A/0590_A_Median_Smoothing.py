# Contest 590, Problem A: Median Smoothing
# URL: https://codeforces.com/contest/590/problem/A

import sys

input = sys.stdin.readline

n = int(input())
a = list(map(int, input().split()))
ans = 0
l = 0

for r in range(1, n):
    if a[r] == a[r - 1]:
        ans = max(ans, (r - l - 1) // 2)
        midpoint = (l + r) // 2
        for j in range(l, midpoint):
            a[j] = a[l]
        for j in range(midpoint, r):
            a[j] = a[r - 1]
        l = r

ans = max(ans, (n - l - 1) // 2)
midpoint = (l + n) // 2
for j in range(l, midpoint):
    a[j] = a[l]
for j in range(midpoint, n):
    a[j] = a[n - 1]

print(ans)
print(" ".join(str(x) for x in a))