# Contest 2070, Problem D: Tree Jumps
# URL: https://codeforces.com/contest/2070/problem/D

for _ in range(int(input())):
    n = int(input())
    parents = [0, 1] + [*map(int, input().split())]
    levels = [0, 1] + [0 for _ in range(n - 1)]
    level_ctr = [0, 1] + [0 for _ in range(n - 1)]

    for i in range(2, n + 1):
        levels[i] = levels[parents[i]] + 1
        level_ctr[levels[i]] += 1
    level_ctr, a = level_ctr[::-1], 0
    for i in range(n - 1):
        a = a * (level_ctr[i] - 1) + level_ctr[i]
    print((a + 1) % 998244353)
