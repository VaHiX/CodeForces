# Contest 2094, Problem B: Bobritto Bandito
# URL: https://codeforces.com/contest/2094/problem/B

for s in [*open(0)][1:]:
    n, m, l, r = map(int, s.split())
    print(l := max(-m, l), l + m)
