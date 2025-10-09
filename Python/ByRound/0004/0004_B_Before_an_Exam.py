# Contest 4, Problem B: Before an Exam
# URL: https://codeforces.com/contest/4/problem/B

d, h = map(int, input().split())
a = [[*map(int, input().split())] for _ in [1] * (d)]
p = q = 0
for i in a:
    p += i[0]
    q += i[1]
if p <= h <= q:
    d = h - p
    o = []
    for f, s in a:
        if d > 0:
            m = min(d, s - f)
            d -= m
            f += m
        o += [f]
    print("YES")
    print(*o)
else:
    print("NO")
