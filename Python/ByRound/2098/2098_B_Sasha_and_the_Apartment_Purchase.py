# Contest 2098, Problem B: Sasha and the Apartment Purchase
# URL: https://codeforces.com/contest/2098/problem/B

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n, k = map(int, input().split())
    a = sorted(list(map(int, input().split())))
    med = (n - k - 1) // 2
    print(a[n - med - 1] - a[med] + 1)
