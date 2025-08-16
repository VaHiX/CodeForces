# Contest 2127, Problem C: Trip Shopping
# URL: https://codeforces.com/contest/2127/problem/C

t = int(input())
for _ in range(t):
    n, k = list(map(int, input().split()))
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    ans = 0
    c = []
    for i in range(0, n):
        ans += abs(a[i] - b[i])
        c.append([min(a[i], b[i]), max(a[i], b[i])])
    c.sort(key=lambda x: x[1])
    mi = 10 ** 18
    for i in range(1, n):
        if c[i][0] < c[i - 1][1]:
            mi = 0
            break
        mi = min(mi,  2 * (c[i][0] - c[i - 1][1]))
    print(ans + mi)