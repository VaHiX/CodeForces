# Contest 2060, Problem C: Game of Mathletes
# URL: https://codeforces.com/contest/2060/problem/C

for _ in range(int(input())):
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    a.sort()
    l = 0
    r = n - 1
    ctr = 0
    while r > l:
        if a[r] + a[l] == k:
            r -= 1
            l += 1
            ctr += 1
        elif a[r] + a[l] > k:
            r -= 1
        elif a[r] + a[l] < k:
            l += 1
    print(ctr)
