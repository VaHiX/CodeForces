# Contest 1415, Problem A: Prison Break
# URL: https://codeforces.com/contest/1415/problem/A

import sys

input = sys.stdin.buffer.readline

t = int(input())
for i in range(t):
    n, m, r, c = [int(x) for x in input().split()]
    sys.stdout.write(f"{max(n-r, r-1)+max(m-c, c-1)}\n")
