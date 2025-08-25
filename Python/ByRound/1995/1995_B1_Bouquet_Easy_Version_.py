# Contest 1995, Problem B1: Bouquet (Easy Version)
# URL: https://codeforces.com/contest/1995/problem/B1

for _ in range(int(input())):
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    a.sort()
    l, r, s = 0, 0, 0
    ans = 0
    while r < n:
        s += a[r]
        while l < n and (a[r] - a[l] > 1 or s > k):
            s -= a[l]
            l += 1
        ans = max(ans, s)
        r += 1
    print(ans)
