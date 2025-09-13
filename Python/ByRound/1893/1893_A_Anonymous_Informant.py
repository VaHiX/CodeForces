# Contest 1893, Problem A: Anonymous Informant
# URL: https://codeforces.com/contest/1893/problem/A

import sys

input = sys.stdin.buffer.readline

for _ in range(int(input())):
    n, k = map(int, input().split())
    b = list(map(int, input().split()))

    j = n - 1
    for i in range(min(n, k)):
        if b[j] <= n:
            j = (j - b[j]) % n
        else:
            print("No")
            break
    else:
        print("Yes")
