# Contest 2059, Problem E1: Stop Gaming (Easy Version)
# URL: https://codeforces.com/contest/2059/problem/E1

# https://codeforces.com/contest/2059

import sys

input = lambda: sys.stdin.readline().rstrip()  # faster!


def solve_case():
    n, m = map(int, input().split())
    a = [list(map(int, input().split())) for _ in range(n)]
    b = [list(map(int, input().split())) for _ in range(n)]

    used = 0
    ra, ca = 0, 0
    for rb in range(n):
        for cb in range(m):
            if b[rb][cb] == a[ra][ca]:
                used += 1
                ca += 1
                if ca == m:
                    ra += 1
                    ca = 0
            elif ra == rb:
                used -= ca
                ca = 0

    ans = n * m - used
    return ans


ans = []
for _ in range(int(input())):
    ans += [str(solve_case())]
print("\n".join(ans))
