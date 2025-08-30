# Contest 2059, Problem B: Cost of the Array
# URL: https://codeforces.com/contest/2059/problem/B

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    if n == k:
        b = [a[j] for j in range(1, n, 2)] + [0]
        for j in range(n // 2 + 1):
            if b[j] != j + 1:
                print(j + 1)
                break
    else:
        if a[1 : n - k + 2].count(1) != n - k + 1:
            print(1)
        else:
            print(2)
