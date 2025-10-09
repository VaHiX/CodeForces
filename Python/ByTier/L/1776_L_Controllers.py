# Contest 1776, Problem L: Controllers
# URL: https://codeforces.com/contest/1776/problem/L

import sys

input = sys.stdin.readline

n = int(input())
p = input().count("+")
m = n - p
for _ in range(int(input())):
    a, b = map(int, input().split())
    if not (min(a, b) * p - max(a, b) * m <= 0 <= max(a, b) * p - min(a, b) * m):
        print("NO")
        continue
    if a == b:
        print("YES" if p == m else "NO")
    else:
        print("YES" if (m * b - p * b) % (b - a) == 0 else "NO")
