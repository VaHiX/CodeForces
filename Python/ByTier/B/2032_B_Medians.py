# Contest 2032, Problem B: Medians
# URL: https://codeforces.com/contest/2032/problem/B

import sys

input = sys.stdin.readline

t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    if n == 1:
        print("1\n1")
    elif k == 1 or k == n:
        print(-1)
    else:
        print(f"3\n{1} {k - k % 2} {k + 1 + k % 2}")
