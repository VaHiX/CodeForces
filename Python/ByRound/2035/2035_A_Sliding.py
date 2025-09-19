# Contest 2035, Problem A: Sliding
# URL: https://codeforces.com/contest/2035/problem/A

for s in [*open(0)][1:]:
    n, m, r, c = map(int, s.split())
    print(m - c + (2 * m - 1) * (n - r))
