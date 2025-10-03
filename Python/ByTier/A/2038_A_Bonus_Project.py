# Contest 2038, Problem A: Bonus Project
# URL: https://codeforces.com/contest/2038/problem/A

n, k = map(int, input().split())
a = list(map(int, input().split()))
b = list(map(int, input().split()))
c = [0] * n
s = 0
for i in range(n - 1, -1, -1):
    temp = a[i] // b[i]
    if s + temp <= k:
        c[i] = temp
    else:
        c[i] = k - s
    s += c[i]

if sum(c) >= k:
    print(*c)
else:
    print("0 " * n)
