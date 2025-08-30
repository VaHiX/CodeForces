# Contest 2051, Problem B: Journey
# URL: https://codeforces.com/contest/2051/problem/B

for _ in range(int(input())):
    n, a, b, c = map(int, input().split())
    q, n = divmod(n, a + b + c)
    q *= 3
    for e in [a, b, c]:
        if n > 0:
            n -= e
            q += 1
    print(q)
