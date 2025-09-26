# Contest 2055, Problem B: Crafting
# URL: https://codeforces.com/contest/2055/problem/B

import sys

input = sys.stdin.readline

t = int(input())
for _ in range(t):
    input()
    l = zip(map(int, input().split()), map(int, input().split()))
    print("YES" if sum(sorted(x - y for x, y in l)[:2]) >= 0 else "NO")
