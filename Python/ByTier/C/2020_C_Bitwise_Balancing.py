# Contest 2020, Problem C: Bitwise Balancing
# URL: https://codeforces.com/contest/2020/problem/C

import sys
 
input = lambda: sys.stdin.readline().strip()
 
for _ in range(int(input())):
    b, c, d = map(int, input().split())
    a = b ^ d
    if (a | b) - (a & c) == d:
        print(a)
    else:
        print(-1)