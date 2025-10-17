# Contest 1359, Problem B: New Theatre Square
# URL: https://codeforces.com/contest/1359/problem/B

for _ in range(int(input())):
    n, m, x, y = map(int, input().split())
    p = 0
    for i in range(n):
        s = input()
        a = s.count(".")
        b = s.count("..")
        p += min(a * x, b * y + (a - 2 * b) * x)
    print(p)
