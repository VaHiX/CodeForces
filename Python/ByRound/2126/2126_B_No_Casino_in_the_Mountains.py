# Contest 2126, Problem B: No Casino in the Mountains
# URL: https://codeforces.com/contest/2126/problem/B

for _ in range(int(input())):
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    i = 0
    c = 0
    x = k
    while i < n:
        if a[i] == 0:
            k -= 1
            i += 1
        elif a[i] == 1:
            k = x
            i += 1
        if k == 0:
            c += 1
            k = x
            i += 1
    print(c)
