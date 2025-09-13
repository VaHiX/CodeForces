# Contest 2139, Problem A: Maple and Multiplication
# URL: https://codeforces.com/contest/2139/problem/A

t = int(input())
from math import lcm as f

for _ in range(t):
    n, m = map(int, input().split())
    l = f(n, m)
    print((l > n) + (l > m))
