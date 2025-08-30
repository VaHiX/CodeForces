# Contest 4, Problem C: Registration System
# URL: https://codeforces.com/contest/4/problem/C

import sys

Z = sys.stdin.readline
D = {}
for _ in range(int(Z())):
    s = Z().strip()
    if s in D:
        print(f"{s}{D[s]}")
        D[s] += 1
    else:
        print("OK")
        D[s] = 1
