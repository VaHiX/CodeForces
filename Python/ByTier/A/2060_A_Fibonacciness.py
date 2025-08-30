# Contest 2060, Problem A: Fibonacciness
# URL: https://codeforces.com/contest/2060/problem/A

for s in [*open(0)][1:]:
    a, b, d, e = map(int, s.split())
    print(4 - len({a + b, d - b, e - d}))
