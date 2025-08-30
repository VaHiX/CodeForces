# Contest 2106, Problem A: Dr. TC
# URL: https://codeforces.com/contest/2106/problem/A

for s in [*open(0)][2::2]:
    a, b = map(s.count, "10")
    print(a * (len(s) - 2) + b)
