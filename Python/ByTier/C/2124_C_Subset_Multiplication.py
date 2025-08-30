# Contest 2124, Problem C: Subset Multiplication
# URL: https://codeforces.com/contest/2124/problem/C

from math import *

for _ in range(int(input())):
    n = int(input())
    b = list(map(int, input().split()))
    x = 1
    for i in range(n - 1):
        x = lcm(x, b[i] // gcd(b[i], b[i + 1]))
    print(x)
