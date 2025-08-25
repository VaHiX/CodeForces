# Contest 1868, Problem A: Fill in the Matrix
# URL: https://codeforces.com/contest/1868/problem/A

import sys

for _ in range(int(input())):
    l = sys.stdin.readline().split()
    n = int(l[0])
    m = int(l[1])
    if m == 1:
        print(0)
        for i in range(n):
            sys.stdout.write(str(0) + "\n")
        continue
    k = min(m, n + 1)
    sys.stdout.write(str(k) + "\n")
    for i in range(k - 1):
        sys.stdout.write(
            " ".join(
                [str((i + j) % k) for j in range(k)] + [str(j) for j in range(k, m)]
            )
            + "\n"
        )
    for i in range(k - 1, n):
        sys.stdout.write(" ".join([str(j) for j in range(m)]) + "\n")
