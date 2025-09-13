# Contest 2112, Problem C: Coloring Game
# URL: https://codeforces.com/contest/2112/problem/C

t = int(input())
d = []
for _ in [0] * t:
    n = int(input())
    d += [(n, sorted(map(int, input().split())))]
for n, a in d:
    m, s = a[-1], a[-2]
    r = 0
    for k in range(2, n):
        x = max(2 * a[k], s if k == n - 1 else m) - a[k]
        i, j = 0, k - 1
        while i < j:
            if a[i] + a[j] > x:
                r += j - i
                j -= 1
            else:
                i += 1
    print(r)
