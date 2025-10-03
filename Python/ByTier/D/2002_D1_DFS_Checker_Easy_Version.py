# Contest 2002, Problem D1: DFS Checker (Easy Version)
# URL: https://codeforces.com/contest/2002/problem/D1

# https://codeforces.com/contest/2002

import sys

input = lambda: sys.stdin.readline().rstrip()  # faster!


def solve_case():
    n, q = map(int, input().split())
    _ = list(map(int, input().split()))
    p = list(map(int, input().split()))
    k = n.bit_length()

    level = [-1] * n
    parent = [-1] * n
    child1 = [-1] * n
    child2 = [-1] * n

    level[0] = 1
    parent[0] = -1
    for i in range(n):
        if level[i] < k:
            child1[i] = i + 1
            child2[i] = i + 2 ** (k - level[i])
            level[child1[i]] = level[child2[i]] = level[i] + 1
            parent[child1[i]] = parent[child2[i]] = i

    ok = [0] * n
    for i in range(n):
        if parent[i] != -1:
            ok[i] = int(p[i] // 2 == p[parent[i]])
    sum_ok = sum(ok)

    ans = ["NO"] * q
    for i in range(q):
        x, y = map(lambda x: int(x) - 1, input().split())
        s = set()
        if parent[x] != -1:
            s |= {x}
        if child1[x] != -1:
            s |= {child1[x], child2[x]}
        if parent[y] != -1:
            s |= {y}
        if child1[y] != -1:
            s |= {child1[y], child2[y]}
        for j in s:
            sum_ok -= ok[j]
            ok[j] = 0
        p[x], p[y] = p[y], p[x]
        for j in s:
            ok[j] = int(p[j] // 2 == p[parent[j]])
            sum_ok += ok[j]
        if sum_ok == n - 1:
            ans[i] = "YES"

    return "\n".join(ans)


ans = []
for _ in range(int(input())):
    ans += [str(solve_case())]
print("\n".join(ans))
