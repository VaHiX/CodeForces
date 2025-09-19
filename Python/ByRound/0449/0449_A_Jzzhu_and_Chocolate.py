# Contest 449, Problem A: Jzzhu and Chocolate
# URL: https://codeforces.com/contest/449/problem/A

for pratyush in range(1):
    n, m, k = list(map(int, input().split()))
    if m > n:
        m, n = n, m
    if k + 1 <= m - 1:
        print(max((n // (k + 1)) * m, (m // (k + 1)) * n))
    elif k + 1 <= n and k + 1 > m - 1:
        print(max((n // (k + 1)) * m, (n // (k - m + 2))))
    elif k <= n + m - 2:
        print(max((n // (k - m + 2)), (m // (k - n + 2))))
    else:
        print(-1)
