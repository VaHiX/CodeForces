# Contest 1700, Problem A: Optimal Path
# URL: https://codeforces.com/contest/1700/problem/A

for i in [*open(0)][1:]:
    n, m = map(int, i.split())
    print(m * (m - 1 + n * n + n) // 2)
