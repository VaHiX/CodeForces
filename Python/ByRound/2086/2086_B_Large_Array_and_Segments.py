# Contest 2086, Problem B: Large Array and Segments
# URL: https://codeforces.com/contest/2086/problem/B

import sys

input = sys.stdin.readline

t = int(input())
for tests in range(t):
    n, k, x = map(int, input().split())
    A = list(map(int, input().split()))

    S = sum(A)

    ko = x // S * n
    x %= S

    for i in range(n - 1, -1, -1):
        if x <= 0:
            break
        x -= A[i]
        ko += 1

    # print(ko)

    print(max(0, n * k - ko + 1))
