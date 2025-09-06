# Contest 2051, Problem D: Counting Pairs
# URL: https://codeforces.com/contest/2051/problem/D

for _ in range(int(input())):
    n, x, y = map(int, input().split())
    a = sorted(map(int, input().split()))
    res, l, r, s = 0, 0, 0, sum(a)
    for i in range(n - 1, -1, -1):
        while l < n and a[l] + a[i] < s - y:
            l += 1
        while r < n and a[r] + a[i] <= s - x:
            r += 1
        res += min(r, i) - min(l, i)

    print(res)
