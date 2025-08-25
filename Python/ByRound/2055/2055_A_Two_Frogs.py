# Contest 2055, Problem A: Two Frogs
# URL: https://codeforces.com/contest/2055/problem/A

for s in [*open(0)][1:]:
    n, a, b = map(int, s.split())
    print("YNEOS"[b - a & 1 :: 2])
