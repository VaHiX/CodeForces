# Contest 2032, Problem A: Circuit
# URL: https://codeforces.com/contest/2032/problem/A

for s in [*open(0)][2::2]:
    m, k = map(s.count, "01")
    print(m % 2, min(m, k))
