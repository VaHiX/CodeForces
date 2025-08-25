# Contest 2085, Problem C: Serval and The Formula
# URL: https://codeforces.com/contest/2085/problem/C

for l in [*open(0)][1:]:
    x, y = map(int, l.split())
    print(-(x == y) or 2**48 - max(x, y))
