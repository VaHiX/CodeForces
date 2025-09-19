# Contest 2109, Problem C3: Hacking Numbers (Hard Version)
# URL: https://codeforces.com/contest/2109/problem/C3

import sys

input = sys.stdin.readline


def ans(*args):
    print(*args if len(args) else "!", flush=True)
    return int(input())


t = int(input())
for _ in range(t):
    n = int(input())
    ans("mul", 999999999)
    ans("digit")
    if n != 81:
        ans("add", n - 81)
    ans()
