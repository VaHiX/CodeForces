# Contest 2093, Problem A: Ideal Generator
# URL: https://codeforces.com/contest/2093/problem/A

for k in [*open(0)][1:]:
    print("YNEOS"[~int(k) & 1 :: 2])
