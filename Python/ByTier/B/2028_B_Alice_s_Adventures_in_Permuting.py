# Contest 2028, Problem B: Alice's Adventures in Permuting
# URL: https://codeforces.com/contest/2028/problem/B

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n, a, b = map(int, input().split())
    if a == 0 and b < n - 2:
        print(-1)
        continue
    if a == 0:
        if b < n:
            print(n - 1)
        else:
            print(n)
        continue
    print(n - max(0, (n - 1 - b) // a + 1))
