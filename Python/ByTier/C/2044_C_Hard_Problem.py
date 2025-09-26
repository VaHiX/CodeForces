# Contest 2044, Problem C: Hard Problem
# URL: https://codeforces.com/contest/2044/problem/C

for s in [*open(0)][1:]:
    m, a, b, c = map(int, s.split())
    x = min(a, m) + min(b, m)
    print(x + min(c, 2 * m - x))
