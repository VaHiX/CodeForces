# Contest 2114, Problem A: Square Year
# URL: https://codeforces.com/contest/2114/problem/A

for n in [*open(0)][1:]:
    print(*([r := int(t := int(n) ** 0.5), 0], [-1])[r < t])
