# Contest 2074, Problem A: Draw a Square
# URL: https://codeforces.com/contest/2074/problem/A

for s in [*open(0)][1:]:
    print("YNEOS"[len({*s.split()}) > 1 :: 2])
