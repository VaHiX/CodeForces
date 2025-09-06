# Contest 1662, Problem A: Organizing SWERC
# URL: https://codeforces.com/contest/1662/problem/A

import sys
input = sys.stdin.readline

M = int(1e9) + 7

def solve():
    n = int(input())
    vis = {i:-1 for i in range(1, 11)}

    for i in range(n):
        b, d = map(int, input().split())
        vis[d] = max(vis[d], b)

    for x in vis.values():
        if x == -1:
            return 'MOREPROBLEMS'
    return sum(vis.values())

for _ in range(int(input())):
    print(solve())