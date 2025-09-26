# Contest 2063, Problem A: Minimal Coprime
# URL: https://codeforces.com/contest/2063/problem/A

for s in [*open(0)][1:]:
    l, r = map(int, s.split())
    print((l == r == 1) + r - l)
