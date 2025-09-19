# Contest 2111, Problem C: Equal Values
# URL: https://codeforces.com/contest/2111/problem/C

for _ in range(int(input())):
    n = int(input())
    arr = [int(x) for x in input().split()]
    res = float("inf")
    l = 0
    for r in range(n):
        if arr[r] != arr[l]:
            l = r
        res = min(res, arr[l] * (n - r + l - 1))

    print(res)
