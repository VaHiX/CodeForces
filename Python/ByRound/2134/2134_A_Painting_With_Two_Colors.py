# Contest 2134, Problem A: Painting With Two Colors
# URL: https://codeforces.com/contest/2134/problem/A

for s in [*open(0)][1:]:
    n, a, b = map(int, s.split())
    print("YNEOS"[n + b & 1 or n + a & 1 and a > b :: 2])
