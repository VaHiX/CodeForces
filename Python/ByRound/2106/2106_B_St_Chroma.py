# Contest 2106, Problem B: St. Chroma
# URL: https://codeforces.com/contest/2106/problem/B

for _ in range(int(input())):
    n, x = map(int, input().split())
    if x < n:
        print(*range(x), *range(x + 1, n), x)
    else:
        print(*range(n))
