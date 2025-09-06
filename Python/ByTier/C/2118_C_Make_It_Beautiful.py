# Contest 2118, Problem C: Make It Beautiful
# URL: https://codeforces.com/contest/2118/problem/C

R = lambda: map(int, input().split())
(t,) = R()
while t:
    t -= 1
    n, k = R()
    a = (*R(),)
    r = i = 0
    for i in range(60):
        b = 1 << i
        i += 1
        j = 0
        for x in a:
            d = ~x & b
            r += k >= d
            k = max(0, k - d)
            j += 1
    print(r)
