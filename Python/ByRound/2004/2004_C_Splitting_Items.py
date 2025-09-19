# Contest 2004, Problem C: Splitting Items
# URL: https://codeforces.com/contest/2004/problem/C

for _ in range(int(input())):
    n, k = map(int, input().split()); a = sorted(map(int, input().split()), reverse = True)
    x = y = 0
    for i in range(n):
        if i & 1: d = min(k, a[i - 1] - a[i]); y += a[i] + d; k -= d
        else: x += a[i]
    print(x - y)