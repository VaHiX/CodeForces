# Contest 2049, Problem B: pspspsps
# URL: https://codeforces.com/contest/2049/problem/B

for s in [*open(0)][2::2]:
    print("YNEOS"["p" in s[:-2] and "s" in s[1:] :: 2])
