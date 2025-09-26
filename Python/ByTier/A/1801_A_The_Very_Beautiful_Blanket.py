# Contest 1801, Problem A: The Very Beautiful Blanket
# URL: https://codeforces.com/contest/1801/problem/A

for l in [*open(0)][1:]:
    n, m = map(int, l.split())
    print(n * m, *[i * 256 + j for i in range(n) for j in range(m)])
