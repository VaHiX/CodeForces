# Contest 2102, Problem A: Dinner Time
# URL: https://codeforces.com/contest/2102/problem/A

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n, m, p, q = map(int, input().split())
    print("yes" if n % p or q * (n // p) == m else "no")
