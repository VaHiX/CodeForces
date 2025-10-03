# Contest 2025, Problem C: New Game
# URL: https://codeforces.com/contest/2025/problem/C

R = lambda: map(int, input().split())
(t,) = R()
while t:
    t -= 1
    n, k = R()
    a = sorted(R())
    r = j = p = 0
    while j < n:
        if a[j] > p:
            i = j
        while a[j] - a[i] >= k:
            i += 1
        p = a[j] + 1
        j += 1
        r = max(r, j - i)
    print(r)
