# Contest 2121, Problem D: 1709
# URL: https://codeforces.com/contest/2121/problem/D

R = lambda: [*map(int, input().split())]
for _ in [0] * R()[0]:
    R()
    a, b = c = R(), R()
    r = []
    j = k = 0
    for l in c:
        j += 1
        for i, x in enumerate(l):
            while i and x < l[i - 1]:
                i -= 1
                r += (j, i + 1)
                l[i : i + 2] = x, l[i]
    for x, y in zip(*c):
        r += (3, k := k + 1) * (x > y)
    print(len(r) // 2, *r)
