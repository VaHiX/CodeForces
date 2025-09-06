# Contest 2108, Problem B: SUMdamental Decomposition
# URL: https://codeforces.com/contest/2108/problem/B

import sys

input = sys.stdin.buffer.readline

for _ in range(int(input())):
    n, x = map(int, input().split())
    bits = bin(x).count("1")
    if n <= bits:
        print(x)
    elif (n - bits) % 2 == 0:
        print(x + n - bits)
    else:
        if x > 1:
            print(x + n - bits + 1)
        elif x == 1:
            print(n + 3)
        else:
            print(-1 if n == 1 else n + 3)
