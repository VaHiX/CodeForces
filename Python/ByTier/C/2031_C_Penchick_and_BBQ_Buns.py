# Contest 2031, Problem C: Penchick and BBQ Buns
# URL: https://codeforces.com/contest/2031/problem/C

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n = int(input())
    if n % 2:
        if n < 27:
            print(-1)
        else:
            out = [
                1,
                2,
                2,
                3,
                3,
                4,
                4,
                5,
                5,
                1,
                6,
                6,
                7,
                7,
                8,
                8,
                9,
                9,
                10,
                10,
                11,
                11,
                12,
                13,
                13,
                1,
                12,
            ]
            st = 28
            while len(out) < n:
                out.append(st // 2)
                st += 1
            print(*out)
    else:
        print(*[j // 2 + 1 for j in range(n)])
