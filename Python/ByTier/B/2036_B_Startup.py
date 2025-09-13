# Contest 2036, Problem B: Startup
# URL: https://codeforces.com/contest/2036/problem/B

for _ in range(int(input())):
    n, k = map(int, input().split())
    c = [0] * (k + 1)
    for i in range(k):
        x, y = map(int, input().split())
        c[x] += y
    c.sort()
    print(sum(c[-n:]))
