# Contest 2043, Problem E: Matrix Transformation
# URL: https://codeforces.com/contest/2043/problem/E

import sys

input = lambda: sys.stdin.readline().strip()
maput = lambda: map(int, input().split())
printf = sys.stdout.write

t = int(input())

for _ in range(t):
    n, m = maput()
    a = [list(maput()) for i in range(n)]
    b = [list(maput()) for i in range(n)]

    for _ in range(min(n, m) + 1):
        for i in range(n):
            ands = 0
            for j in range(m):
                c = a[i][j] ^ b[i][j]
                ands |= c & a[i][j]

            for k in range(m):
                a[i][k] &= ~ands

        for j in range(m):
            ors = 0
            for i in range(n):
                c = a[i][j] ^ b[i][j]
                ors |= c & b[i][j]

            for k in range(n):
                a[k][j] |= ors

        if a == b:
            break
    else:
        # print(a, b)
        printf("No\n")
        continue
    printf("Yes\n")
